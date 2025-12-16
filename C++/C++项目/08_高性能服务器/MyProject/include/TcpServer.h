#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "noncopyable.h"
#include "InetAddress.h"
#include <functional>
#include <string>
#include <unordered_map>
#include <memory>

class EventLoop;
class Acceptor;
class TcpConnection;

/**
 * TCP服务器类
 * 管理TCP连接的生命周期，包括监听、接受连接和关闭连接
 */
class TcpServer : noncopyable
{
public:
    using ThreadInitCallback = std::function<void(EventLoop *)>;
    using ConnectionCallback = std::function<void(const std::shared_ptr<TcpConnection> &)>;
    using MessageCallback = std::function<void(const std::shared_ptr<TcpConnection> &, std::string &)>;
    using WriteCompleteCallback = std::function<void(const std::shared_ptr<TcpConnection> &)>;
    using CloseCallback = std::function<void(const std::shared_ptr<TcpConnection> &)>;

    /**
     * 构造函数
     * @param loop 事件循环对象
     * @param listenAddr 监听地址和端口
     * @param nameArg 服务器名称
     */
    TcpServer(EventLoop *loop,
              const InetAddress &listenAddr,
              const std::string &nameArg);

    /**
     * 析构函数
     */
    ~TcpServer();

    /**
     * 启动服务器
     */
    void start();

    /**
     * 设置线程初始化回调函数
     */
    void setThreadInitCallback(const ThreadInitCallback &cb) { threadInitCallback_ = cb; }

    /**
     * 设置连接建立回调函数
     */
    void setConnectionCallback(const ConnectionCallback &cb) { connectionCallback_ = cb; }

    /**
     * 设置消息到达回调函数
     */
    void setMessageCallback(const MessageCallback &cb) { messageCallback_ = cb; }

    /**
     * 设置写完成回调函数
     */
    void setWriteCompleteCallback(const WriteCompleteCallback &cb) { writeCompleteCallback_ = cb; }

    /**
     * 设置连接关闭回调函数
     */
    void setCloseCallback(const CloseCallback &cb) { closeCallback_ = cb; }

    /**
     * 获取服务器名称
     */
    const std::string &name() const { return name_; }

    /**
     * 获取监听地址
     */
    const InetAddress &listenAddress() const { return listenAddr_; }

private:
    /**
     * 处理新连接
     * @param sockfd 新连接的socket文件描述符
     * @param peerAddr 客户端地址
     */
    void newConnection(int sockfd, const InetAddress &peerAddr);

    /**
     * 移除连接
     * @param conn TCP连接对象
     */
    void removeConnection(const std::shared_ptr<TcpConnection> &conn);

    /**
     * 在事件循环中移除连接
     * @param conn TCP连接对象
     */
    void removeConnectionInLoop(const std::shared_ptr<TcpConnection> &conn);

    /**
     * 处理消息
     * @param conn TCP连接对象
     * @param message 接收到的消息
     */
    void handleMessage(const std::shared_ptr<TcpConnection> &conn, std::string &message);

    using ConnectionMap = std::unordered_map<std::string, std::shared_ptr<TcpConnection>>;

    EventLoop *loop_;                    // 事件循环
    const std::string name_;             // 服务器名称
    std::unique_ptr<Acceptor> acceptor_; // 接受新连接的对象

    ThreadInitCallback threadInitCallback_;       // 线程初始化回调
    ConnectionCallback connectionCallback_;       // 连接建立回调
    MessageCallback messageCallback_;             // 消息到达回调
    WriteCompleteCallback writeCompleteCallback_; // 写完成回调
    CloseCallback closeCallback_;                 // 连接关闭回调

    ConnectionMap connections_;    // 连接列表
    const InetAddress listenAddr_; // 监听地址
    int nextConnId_;               // 下一个连接ID
};

#endif // TCPSERVER_H