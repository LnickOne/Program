#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main()
{
    // 1.创建一个套接字socket
    int client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock == -1)
    {
        std::cout << "socket create error" << std::endl;
        return -1;
    }
    // 2.连接服务器
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr)); // 清零整个结构
    server_addr.sin_family = AF_INET;             // 设置地址族为IPv4
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr.s_addr);
    server_addr.sin_port = htons(6666);
    if (connect(client_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        std::cout << "connect error" << std::endl;
        return -1;
    }
    std::cout << "连接服务器成功" << std::endl;

    // 3.数据交互
    std::string msg = "Hello, server!";

    if (write(client_sock, msg.c_str(), msg.size()) == -1)
    {
        std::cout << "write error" << std::endl;
        return -1;
    }
    // 接收消息
    char buffer[1024] = {0};                                       // 初始化缓冲区为0，防止乱码
    int read_size = read(client_sock, buffer, sizeof(buffer) - 1); // 留一个字节给终止符

    if (read_size == -1)
    {
        std::cout << "read error" << std::endl;
        return -1;
    }
    else if (read_size == 0)
    {
        std::cout << "服务器已关闭连接" << std::endl;
        return -1;
    }

    buffer[read_size] = '\0'; // 确保字符串正确终止
    std::cout << "接收到服务器的数据：" << buffer << std::endl;
    // 4.关闭套接字
    close(client_sock);

    return 0;
}