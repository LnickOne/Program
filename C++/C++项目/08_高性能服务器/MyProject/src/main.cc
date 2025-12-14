#include "noncopyable.h"
#include "InetAddress.h"
#include "Socket.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    // 创建InetAddress对象
    InetAddress addr(8888, "127.0.0.1");
    std::cout << "IP: " << addr.toIp() << std::endl;
    std::cout << "Port: " << addr.toPort() << std::endl;
    std::cout << "IP:Port: " << addr.toIpPort() << std::endl;

    // 创建Socket对象
    int listenfd = ::socket(AF_INET, SOCK_STREAM, 0);
    // 设置非阻塞
    int flags = ::fcntl(listenfd, F_GETFL, 0);
    ::fcntl(listenfd, F_SETFL, flags | O_NONBLOCK);
    // 设置CLOEXEC
    flags = ::fcntl(listenfd, F_GETFD, 0);
    ::fcntl(listenfd, F_SETFD, flags | FD_CLOEXEC);
    Socket socket(listenfd);

    // 绑定地址
    socket.bindAddress(addr);

    // 监听连接
    socket.listen();

    std::cout << "Server is listening on " << addr.toIpPort() << std::endl;

    // 等待连接
    InetAddress peeraddr;
    int connfd = socket.accept(&peeraddr);
    if (connfd >= 0)
    {
        std::cout << "New connection from " << peeraddr.toIpPort() << std::endl;
        ::close(connfd);
    }

    return 0;
}