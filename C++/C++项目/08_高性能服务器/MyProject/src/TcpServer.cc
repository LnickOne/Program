#include "TcpServer.h"
#include "Acceptor.h"
#include "EventLoop.h"
#include "TcpConnection.h"
#include "Logger.h"
#include <string.h>
#include <cassert>
#include <unistd.h>

/**
 * TcpServer构造函数
 */
TcpServer::TcpServer(EventLoop *loop, const InetAddress &listenAddr, const std::string &nameArg)
    : loop_(loop),
      name_(nameArg),
      acceptor_(new Acceptor(loop, listenAddr)),
      threadInitCallback_(),
      connectionCallback_(),
      messageCallback_(),
      writeCompleteCallback_(),
      closeCallback_(),
      nextConnId_(1)
{
    // 设置新连接回调函数
    acceptor_->setNewConnectionCallback(
        std::bind(&TcpServer::newConnection, this, std::placeholders::_1, std::placeholders::_2));
    LOG_INFO << "TcpServer构造函数：服务器 [" << name_ << "] 创建成功";
}

/**
 * TcpServer析构函数
 */
TcpServer::~TcpServer()
{
    LOG_INFO << "TcpServer析构函数：服务器 [" << name_ << "] 销毁";
    for (auto &item : connections_)
    {
        std::shared_ptr<TcpConnection> conn(item.second);
        item.second.reset();
        conn->getLoop()->runInLoop(
            std::bind(&TcpConnection::connectDestroyed, conn));
    }
}

/**
 * 启动服务器
 */
void TcpServer::start()
{
    if (acceptor_->listenning())
    {
        return;
    }
    // 调用Acceptor的listen方法
    acceptor_->listen();
    LOG_INFO << "TcpServer::start [" << name_ << "]：开始监听 " << listenAddr_.toIpPort();
}

/**
 * 处理新连接
 * @param sockfd 新连接的socket文件描述符
 * @param peerAddr 客户端地址
 */
void TcpServer::newConnection(int sockfd, const InetAddress &peerAddr)
{
    loop_->assertInLoopThread();
    char buf[32];
    snprintf(buf, sizeof buf, "#%d", nextConnId_);
    ++nextConnId_;
    std::string connName = name_ + buf;

    InetAddress localAddr;
    socklen_t addrlen = sizeof localAddr;
    if (::getsockname(sockfd, (struct sockaddr *)localAddr.getSockAddr(), &addrlen) < 0)
    {
        LOG_ERROR << "TcpServer::newConnection：getsockname错误";
        ::close(sockfd);
        return;
    }

    LOG_INFO << "TcpServer::newConnection [" << name_ << "]：新连接 [" << connName
             << "] 来自 " << peerAddr.toIpPort();

    // 创建TcpConnection对象
    std::shared_ptr<TcpConnection> conn =
        std::make_shared<TcpConnection>(loop_, connName, sockfd, localAddr, peerAddr);

    connections_[connName] = conn;

    // 设置回调函数
    conn->setConnectionCallback(connectionCallback_);
    conn->setMessageCallback(std::bind(&TcpServer::handleMessage, this,
                                       std::placeholders::_1, std::placeholders::_2));
    conn->setWriteCompleteCallback(writeCompleteCallback_);
    conn->setCloseCallback(
        std::bind(&TcpServer::removeConnection, this, std::placeholders::_1));

    // 建立连接
    conn->connectEstablished();
}

/**
 * 移除连接
 * @param conn TCP连接对象
 */
void TcpServer::removeConnection(const std::shared_ptr<TcpConnection> &conn)
{
    loop_->runInLoop(
        std::bind(&TcpServer::removeConnectionInLoop, this, conn));
}

/**
 * 在事件循环中移除连接
 * @param conn TCP连接对象
 */
void TcpServer::removeConnectionInLoop(const std::shared_ptr<TcpConnection> &conn)
{
    loop_->assertInLoopThread();
    LOG_INFO << "TcpServer::removeConnectionInLoop [" << name_ << "] - connection [" << conn->name() << "]";
    size_t n = connections_.erase(conn->name());
    (void)n;
    assert(n == 1);
    conn->connectDestroyed();
}

/**
 * 处理消息
 * @param conn TCP连接对象
 * @param message 接收到的消息
 */
void TcpServer::handleMessage(const std::shared_ptr<TcpConnection> &conn, std::string &message)
{
    LOG_INFO << "TcpServer::handleMessage [" << name_ << "] - received " << message.size()
             << " bytes from connection [" << conn->name() << "]";
    // 处理消息，可以传递给用户提供的回调函数
    if (messageCallback_)
    {
        // 直接传递消息引用给回调函数
        messageCallback_(conn, message);
    }
}