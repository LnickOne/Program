#include "Acceptor.h"
#include "EventLoop.h"
#include "Socket.h"
#include "Channel.h"
#include "Logger.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * Acceptor构造函数
 */
Acceptor::Acceptor(EventLoop *loop, const InetAddress &listenAddr)
    : loop_(loop),
      acceptSocket_(new Socket(socket(AF_INET, SOCK_STREAM, 0))),
      acceptChannel_(new Channel(loop, acceptSocket_->fd())),
      newConnectionCallback_(),
      listenning_(false),
      idleFd_(::open("/dev/null", O_RDONLY | O_CLOEXEC))
{
    if (idleFd_ < 0)
    {
        LOG_ERROR << "Acceptor构造函数：打开/dev/null失败";
    }

    // 设置socket选项
    acceptSocket_->setReuseAddr(true);
    acceptSocket_->setReusePort(true);
    acceptSocket_->setNonBlocking();
    // 绑定地址
    acceptSocket_->bindAddress(listenAddr);
    // 设置可读事件回调
    acceptChannel_->setReadCallback(
        std::bind(&Acceptor::handleRead, this));
}

/**
 * Acceptor析构函数
 */
Acceptor::~Acceptor()
{
    acceptChannel_->disableAll();
    acceptChannel_->remove();
    ::close(idleFd_);
    LOG_DEBUG << "Acceptor析构函数：关闭idleFd=" << idleFd_;
}

/**
 * 开始监听
 */
void Acceptor::listen()
{
    listenning_ = true;
    acceptSocket_->listen();
    acceptChannel_->enableReading();
    LOG_DEBUG << "Acceptor::listen：开始监听 " << acceptSocket_->fd();
}

/**
 * 处理可读事件（新连接）
 */
void Acceptor::handleRead()
{
    loop_->assertInLoopThread();
    InetAddress peerAddr;
    int connfd = acceptSocket_->accept(&peerAddr);
    if (connfd >= 0)
    {
        LOG_INFO << "Acceptor::handleRead：接受来自 " << peerAddr.toIpPort()
                 << " 的新连接，connfd=" << connfd;
        if (newConnectionCallback_)
        {
            newConnectionCallback_(connfd, peerAddr);
        }
        else
        {
            ::close(connfd);
            LOG_WARN << "Acceptor::handleRead：未设置newConnectionCallback_，关闭connfd=" << connfd;
        }
    }
    else
    {
        LOG_ERROR << "Acceptor::handleRead：接受连接错误";
        // 文件描述符耗尽处理
        if (errno == EMFILE)
        {
            ::close(idleFd_);
            idleFd_ = ::accept(acceptSocket_->fd(), NULL, NULL);
            ::close(idleFd_);
            idleFd_ = ::open("/dev/null", O_RDONLY | O_CLOEXEC);
            LOG_WARN << "Acceptor::handleRead：文件描述符耗尽，通过关闭并重新打开idleFd处理";
        }
    }
}