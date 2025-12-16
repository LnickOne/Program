#include "Socket.h"
#include "InetAddress.h"
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/tcp.h>

Socket::Socket(int sockfd) : sockfd_(sockfd)
{
}

Socket::~Socket()
{
    ::close(sockfd_);
}

void Socket::bindAddress(const InetAddress &localaddr)
{
    if (::bind(sockfd_, (const sockaddr *)localaddr.getSockAddr(), sizeof(sockaddr_in)) < 0)
    {
        // 处理错误
    }
}

void Socket::listen()
{
    if (::listen(sockfd_, SOMAXCONN) < 0)
    {
        // 处理错误
    }
}

int Socket::accept(InetAddress *peeraddr)
{
    sockaddr_in addr;
    socklen_t len = sizeof addr;
    int connfd = ::accept(sockfd_, (sockaddr *)&addr, &len);
    if (connfd >= 0)
    {
        peeraddr->setSockAddr(addr);
        // 设置非阻塞
        int flags = ::fcntl(connfd, F_GETFL, 0);
        ::fcntl(connfd, F_SETFL, flags | O_NONBLOCK);
        // 设置CLOEXEC
        flags = ::fcntl(connfd, F_GETFD, 0);
        ::fcntl(connfd, F_SETFD, flags | FD_CLOEXEC);
    }
    return connfd;
}

void Socket::shutdownWrite()
{
    ::shutdown(sockfd_, SHUT_WR);
}

void Socket::setTcpNoDelay(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof optval);
}

void Socket::setReuseAddr(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
}

void Socket::setReusePort(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof optval);
}

void Socket::setKeepAlive(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof optval);
}

void Socket::setNonBlocking()
{
    int flags = ::fcntl(sockfd_, F_GETFL, 0);
    if (flags < 0)
    {
        // 处理错误
        return;
    }
    ::fcntl(sockfd_, F_SETFL, flags | O_NONBLOCK);
}

int Socket::getSocketError() const
{
    int optval;
    socklen_t optlen = sizeof optval;
    if (::getsockopt(sockfd_, SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0)
    {
        return errno;
    }
    return optval;
}