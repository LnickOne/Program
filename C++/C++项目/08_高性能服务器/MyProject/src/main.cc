#include <iostream>
#include "EventLoop.h"
#include "Logger.h"
#include "TcpServer.h"
#include "InetAddress.h"
#include "TcpConnection.h"
#include <string>

// 连接建立回调函数
void onConnection(const std::shared_ptr<TcpConnection> &conn)
{
    if (conn->connected())
    {
        LOG_INFO << "onConnection(): new connection [" << conn->name()
                 << "] from " << conn->peerAddress().toIpPort();
        // 发送欢迎消息
        conn->send("Welcome to MyTcpServer!\r\n");
    }
    else
    {
        LOG_INFO << "onConnection(): connection [" << conn->name()
                 << "] is down";
    }
}

// 消息到达回调函数
void onMessage(const std::shared_ptr<TcpConnection> &conn, std::string &message)
{
    LOG_INFO << "onMessage(): received " << message.size()
             << " bytes from connection [" << conn->name() << "]: " << message;
    // 回显消息给客户端
    conn->send(message);
}

// 写完成回调函数
void onWriteComplete(const std::shared_ptr<TcpConnection> &conn)
{
    LOG_INFO << "onWriteComplete(): connection [" << conn->name() << "] write complete";
}

// 连接关闭回调函数
void onClose(const std::shared_ptr<TcpConnection> &conn)
{
    LOG_INFO << "onClose(): connection [" << conn->name() << "] is closed";
}

int main()
{
    // 初始化日志系统
    setLogLevel(INFO);

    // 创建一个事件循环对象
    EventLoop loop;

    // 设置服务器监听地址和端口
    InetAddress listenAddr(8080);

    // 创建TCP服务器实例
    TcpServer server(&loop, listenAddr, "MyTcpServer");

    // 设置回调函数
    server.setConnectionCallback(onConnection);
    server.setMessageCallback(onMessage);
    server.setWriteCompleteCallback(onWriteComplete);
    server.setCloseCallback(onClose);

    // 启动服务器
    server.start();

    LOG_INFO << "MyTcpServer is running on port 8080...";

    // 运行事件循环
    loop.loop();

    return 0;
}