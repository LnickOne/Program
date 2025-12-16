#include "TcpConnection.h"
#include "EventLoop.h"
#include "Channel.h"
#include "Socket.h"
#include "Logger.h"
#include "Timestamp.h"
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <cassert>
#include <cstdio>

/**
 * TcpConnection构造函数
 */
TcpConnection::TcpConnection(EventLoop *loop,
                             const std::string &name,
                             int sockfd,
                             const InetAddress &localAddr,
                             const InetAddress &peerAddr)
    : loop_(loop),
      name_(name),
      state_(kConnecting),
      socket_(new Socket(sockfd)),
      channel_(new Channel(loop, sockfd)),
      localAddr_(localAddr),
      peerAddr_(peerAddr)
{
    LOG_DEBUG << "TcpConnection::TcpConnection [" << name_ << "] at " << this
              << " fd=" << sockfd;

    // 设置通道的事件回调函数
    channel_->setReadCallback(
        std::bind(&TcpConnection::handleRead, this, std::placeholders::_1));
    channel_->setWriteCallback(
        std::bind(&TcpConnection::handleWrite, this));
    channel_->setCloseCallback(
        std::bind(&TcpConnection::handleClose, this));
    channel_->setErrorCallback(
        std::bind(&TcpConnection::handleError, this));
}

/**
 * TcpConnection析构函数
 */
TcpConnection::~TcpConnection()
{
    LOG_DEBUG << "TcpConnection::~TcpConnection [" << name_ << "] at " << this
              << " fd=" << channel_->fd()
              << " state=" << stateToString();
}

/**
 * 将连接状态转换为字符串
 * @return 状态字符串
 */
const char *TcpConnection::stateToString() const
{
    switch (state_)
    {
    case kDisconnected:
        return "kDisconnected";
    case kConnecting:
        return "kConnecting";
    case kConnected:
        return "kConnected";
    case kDisconnecting:
        return "kDisconnecting";
    default:
        return "unknown state";
    }
}

/**
 * 发送数据
 */
void TcpConnection::send(const std::string &message)
{
    if (state_ == kConnected)
    {
        if (loop_->isInLoopThread())
        {
            sendInLoop(message);
        }
        else
        {
            loop_->runInLoop(
                std::bind(&TcpConnection::sendInLoop,
                          this,
                          message));
        }
    }
}

/**
 * 在事件循环线程中发送数据
 */
void TcpConnection::sendInLoop(const std::string &message)
{
    loop_->assertInLoopThread();
    ssize_t nwrote = 0;
    size_t remaining = message.size();
    bool faultError = false;

    // 如果连接正在关闭，或者输出缓冲区不为空，不尝试直接写入
    if (state_ == kDisconnecting || (state_ == kConnected && !channel_->isWriting()))
    {
        nwrote = write(channel_->fd(), message.data(), message.size());
        if (nwrote >= 0)
        {
            remaining = message.size() - nwrote;
            if (remaining == 0 && writeCompleteCallback_)
            {
                loop_->queueInLoop(
                    std::bind(writeCompleteCallback_, shared_from_this()));
            }
        }
        else
        {
            nwrote = 0;
            if (errno != EWOULDBLOCK)
            {
                LOG_ERROR << "TcpConnection::sendInLoop [" << name_ << "] write error";
                if (errno == EPIPE || errno == ECONNRESET)
                {
                    faultError = true;
                }
            }
        }
    }

    // 如果还有剩余数据需要发送，且没有错误，将数据添加到输出缓冲区
    if (!faultError && remaining > 0)
    {
        LOG_DEBUG << "TcpConnection::sendInLoop [" << name_ << "] remaining data=" << remaining;
        outputBuffer_.append(message.data() + nwrote, remaining);
        if (!channel_->isWriting())
        {
            channel_->enableWriting();
        }
    }
}

/**
 * 关闭连接
 */
void TcpConnection::shutdown()
{
    if (state_ == kConnected)
    {
        setState(kDisconnecting);
        loop_->runInLoop(
            std::bind(&TcpConnection::shutdownInLoop, this));
    }
}

/**
 * 在事件循环线程中关闭连接
 */
void TcpConnection::shutdownInLoop()
{
    loop_->assertInLoopThread();
    if (!channel_->isWriting())
    {
        socket_->shutdownWrite();
    }
}

/**
 * 强制关闭连接
 */
void TcpConnection::forceClose()
{
    if (state_ == kConnected || state_ == kDisconnecting)
    {
        setState(kDisconnecting);
        loop_->queueInLoop(
            std::bind(&TcpConnection::forceCloseInLoop, this));
    }
}

/**
 * 在事件循环线程中强制关闭连接
 */
void TcpConnection::forceCloseInLoop()
{
    loop_->assertInLoopThread();
    if (state_ == kConnected || state_ == kDisconnecting)
    {
        handleClose();
    }
}

/**
 * 设置TCP_NODELAY选项
 */
void TcpConnection::setTcpNoDelay(bool on)
{
    socket_->setTcpNoDelay(on);
}

/**
 * 连接建立
 */
void TcpConnection::connectEstablished()
{
    loop_->assertInLoopThread();
    assert(state_ == kConnecting);
    setState(kConnected);
    channel_->tie(shared_from_this());
    channel_->enableReading();

    // 调用连接建立回调函数
    if (connectionCallback_)
    {
        connectionCallback_(shared_from_this());
    }
}

/**
 * 连接销毁
 */
void TcpConnection::connectDestroyed()
{
    loop_->assertInLoopThread();
    if (state_ == kConnected)
    {
        setState(kDisconnected);
        channel_->disableAll();
        connectionCallback_(shared_from_this());
    }
    channel_->remove();
}

/**
 * 处理读事件
 */
void TcpConnection::handleRead(Timestamp receiveTime)
{
    (void)receiveTime; // 消除未使用参数的警告
    loop_->assertInLoopThread();
    int savedErrno = 0;
    char buf[65536]; // 64KB缓冲区
    ssize_t n = read(channel_->fd(), buf, sizeof buf);

    if (n > 0)
    {
        // 读取成功，处理接收到的数据
        inputBuffer_.append(buf, n);
        if (messageCallback_)
        {
            messageCallback_(shared_from_this(), inputBuffer_);
        }
    }
    else if (n == 0)
    {
        // 连接关闭
        handleClose();
    }
    else
    {
        // 读取错误
        savedErrno = errno;
        LOG_ERROR << "TcpConnection::handleRead [" << name_ << "] error";
        handleError();
    }
}

/**
 * 处理写事件
 */
void TcpConnection::handleWrite()
{
    loop_->assertInLoopThread();
    if (channel_->isWriting())
    {
        ssize_t n = write(channel_->fd(), outputBuffer_.data(), outputBuffer_.size());
        if (n > 0)
        {
            outputBuffer_.erase(0, n);
            if (outputBuffer_.empty())
            {
                channel_->disableWriting();
                if (writeCompleteCallback_)
                {
                    loop_->queueInLoop(
                        std::bind(writeCompleteCallback_, shared_from_this()));
                }
                if (state_ == kDisconnecting)
                {
                    shutdownInLoop();
                }
            }
        }
        else
        {
            LOG_ERROR << "TcpConnection::handleWrite [" << name_ << "] error";
        }
    }
    else
    {
        LOG_DEBUG << "TcpConnection::handleWrite [" << name_ << "] is down, no more writing";
    }
}

/**
 * 处理关闭事件
 */
void TcpConnection::handleClose()
{
    loop_->assertInLoopThread();
    LOG_DEBUG << "TcpConnection::handleClose [" << name_ << "] fd=" << channel_->fd()
              << " state=" << this->stateToString();
    assert(state_ == kConnected || state_ == kDisconnecting);
    setState(kDisconnected);
    channel_->disableAll();

    std::shared_ptr<TcpConnection> guardThis(shared_from_this());
    connectionCallback_(guardThis);
    // 调用连接关闭回调函数
    closeCallback_(guardThis);
}

/**
 * 处理错误事件
 */
void TcpConnection::handleError()
{
    int err = socket_->getSocketError();
    LOG_ERROR << "TcpConnection::handleError [" << name_ << "] SO_ERROR=" << err
              << " " << strerror(err);
}