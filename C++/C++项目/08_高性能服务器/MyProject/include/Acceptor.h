#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "noncopyable.h"
#include "InetAddress.h"
#include <functional>
#include <memory>

class EventLoop;
class Channel;
class Socket;

/**
 * Acceptor类
 * 负责监听新的连接请求，并在有新连接时调用回调函数
 */
class Acceptor : noncopyable
{
public:
    using NewConnectionCallback = std::function<void(int sockfd, const InetAddress &peerAddr)>;

    /**
     * 构造函数
     * @param loop 事件循环对象
     * @param listenAddr 监听地址和端口
     */
    Acceptor(EventLoop *loop, const InetAddress &listenAddr);

    /**
     * 析构函数
     */
    ~Acceptor();

    /**
     * 设置新连接回调函数
     */
    void setNewConnectionCallback(const NewConnectionCallback &cb) { newConnectionCallback_ = cb; }

    /**
     * 开始监听
     */
    void listen();

    /**
     * 判断是否正在监听
     */
    bool listenning() const { return listenning_; }

private:
    /**
     * 处理可读事件（新连接）
     */
    void handleRead();

    EventLoop *loop_;                             // 事件循环
    std::unique_ptr<Socket> acceptSocket_;        // 监听socket
    std::unique_ptr<Channel> acceptChannel_;      // 监听socket的Channel
    NewConnectionCallback newConnectionCallback_; // 新连接回调函数
    bool listenning_;                             // 是否正在监听
    int idleFd_;                                  // 空闲文件描述符，用于解决文件描述符耗尽问题
};

#endif // ACCEPTOR_H