#ifndef MY_PROJECT_TCP_CONNECTION_H
#define MY_PROJECT_TCP_CONNECTION_H

#include <memory>
#include <string>
#include <functional>
#include <any>
#include "noncopyable.h"
#include "InetAddress.h"
#include "Timestamp.h"

class EventLoop;
class Channel;
class Socket;

/**
 * TCP连接类
 * 管理TCP连接的生命周期和IO事件
 */
class TcpConnection : noncopyable, public std::enable_shared_from_this<TcpConnection>
{
public:
    /**
     * 连接状态枚举
     */
    enum StateE
    {
        kDisconnected, // 已断开连接
        kConnecting,   // 连接中
        kConnected,    // 已连接
        kDisconnecting // 断开连接中
    };

    /**
     * 构造函数
     * @param loop 事件循环
     * @param name 连接名称
     * @param sockfd 套接字文件描述符
     * @param localAddr 本地地址
     * @param peerAddr 对等方地址
     */
    TcpConnection(EventLoop *loop,
                  const std::string &name,
                  int sockfd,
                  const InetAddress &localAddr,
                  const InetAddress &peerAddr);

    /**
     * 析构函数
     */
    ~TcpConnection();

    /**
     * 获取事件循环
     * @return 事件循环指针
     */
    EventLoop *getLoop() const { return loop_; }

    /**
     * 获取连接名称
     * @return 连接名称
     */
    const std::string &name() const { return name_; }

    /**
     * 获取本地地址
     * @return 本地地址
     */
    const InetAddress &localAddress() const { return localAddr_; }

    /**
     * 获取对等方地址
     * @return 对等方地址
     */
    const InetAddress &peerAddress() const { return peerAddr_; }

    /**
     * 获取连接状态的字符串表示
     * @return 状态字符串
     */
    const char *stateToString() const;

    /**
     * 连接是否已建立
     * @return 是否已连接
     */
    bool connected() const { return state_ == kConnected; }

    /**
     * 连接是否已断开
     * @return 是否已断开连接
     */
    bool disconnected() const { return state_ == kDisconnected; }

    /**
     * 发送数据
     * @param message 要发送的数据
     */
    void send(const std::string &message);

    /**
     * 关闭连接
     */
    void shutdown();

    /**
     * 强制关闭连接
     */
    void forceClose();

    /**
     * 设置TCP连接的保活选项
     * @param on 是否启用保活
     */
    void setTcpNoDelay(bool on);

    /**
     * 设置连接建立回调函数
     * @param cb 回调函数
     */
    void setConnectionCallback(const std::function<void(const std::shared_ptr<TcpConnection> &)> &cb)
    {
        connectionCallback_ = cb;
    }

    /**
     * 设置消息到达回调函数
     * @param cb 回调函数
     */
    void setMessageCallback(const std::function<void(const std::shared_ptr<TcpConnection> &, std::string &)> &cb)
    {
        messageCallback_ = cb;
    }

    /**
     * 设置写入完成回调函数
     * @param cb 回调函数
     */
    void setWriteCompleteCallback(const std::function<void(const std::shared_ptr<TcpConnection> &)> &cb)
    {
        writeCompleteCallback_ = cb;
    }

    /**
     * 设置连接关闭回调函数
     * @param cb 回调函数
     */
    void setCloseCallback(const std::function<void(const std::shared_ptr<TcpConnection> &)> &cb)
    {
        closeCallback_ = cb;
    }

    /**
     * 连接建立
     */
    void connectEstablished();

    /**
     * 连接销毁
     */
    void connectDestroyed();

    /**
     * 设置连接上下文
     * @param context 上下文对象
     */
    void setContext(const std::any& context) {
        context_ = context;
    }

    /**
     * 获取连接上下文
     * @return 上下文对象
     */
    const std::any& getContext() const {
        return context_;
    }

    /**
     * 获取可修改的连接上下文
     * @return 上下文对象
     */
    std::any* getMutableContext() {
        return &context_;
    }

private:
    /**
     * 处理读事件
     */
    void handleRead(Timestamp receiveTime);

    /**
     * 处理写事件
     */
    void handleWrite();

    /**
     * 处理关闭事件
     */
    void handleClose();

    /**
     * 处理错误事件
     */
    void handleError();

    /**
     * 发送数据的内部实现
     * @param message 要发送的数据
     */
    void sendInLoop(const std::string &message);

    /**
     * 关闭连接的内部实现
     */
    void shutdownInLoop();

    /**
     * 强制关闭连接的内部实现
     */
    void forceCloseInLoop();

    /**
     * 设置连接状态
     * @param s 新状态
     */
    void setState(StateE s) { state_ = s; }

    EventLoop *loop_;                  // 事件循环
    std::string name_;                 // 连接名称
    StateE state_;                     // 连接状态
    std::unique_ptr<Socket> socket_;   // 套接字
    std::unique_ptr<Channel> channel_; // 通道
    InetAddress localAddr_;            // 本地地址
    InetAddress peerAddr_;             // 对等方地址

    // 回调函数
    std::function<void(const std::shared_ptr<TcpConnection> &)> connectionCallback_;             // 连接建立回调
    std::function<void(const std::shared_ptr<TcpConnection> &, std::string &)> messageCallback_; // 消息到达回调
    std::function<void(const std::shared_ptr<TcpConnection> &)> writeCompleteCallback_;          // 写入完成回调
    std::function<void(const std::shared_ptr<TcpConnection> &)> closeCallback_;                  // 连接关闭回调

    std::string inputBuffer_;  // 输入缓冲区
    std::string outputBuffer_; // 输出缓冲区
    std::any context_;         // 连接上下文
};

#endif // MY_PROJECT_TCP_CONNECTION_H