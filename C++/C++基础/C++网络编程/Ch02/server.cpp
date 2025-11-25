#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h> //ip地址的操作api
#include <arpa/inet.h>  //ip地址的操作api
#include <unistd.h>     //操作系统的api
#include <cstring>
int main(int, char **)
{
    // 1.创建一个套接字
    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock == -1)
    {
        std::cout << "socket create error" << std::endl;
        return -1;
    }

    // 2.绑定IP地址信息和端口号
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(6666);

    if (bind(listen_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        std::cout << "bind error" << std::endl;
        return -1;
    }

    // 3.监听套接字
    if (listen(listen_sock, 5) == -1)
    {
        std::cout << "listen error" << std::endl;
        return -1;
    }
    std::cout << "服务器启动成功，等待客户端连接..." << std::endl;

    // 4.接受客户端连接
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    int client_sock = accept(listen_sock, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_sock == -1)
    {
        std::cout << "accept error" << std::endl;
        return -1;
    }
    // 5.数据交互

    // 接收消息
    char buffer[1024] = {0};                                       // 初始化缓冲区为0，防止乱码
    int read_size = read(client_sock, buffer, sizeof(buffer) - 1); // 修改：使用client_sock而不是listen_sock
    if (read_size == -1)
    {
        std::cout << "read error" << std::endl;
        return -1;
    }
    else if (read_size == 0)
    {
        std::cout << "客户端已关闭连接" << std::endl;
        return -1;
    }

    buffer[read_size] = '\0'; // 确保字符串正确终止
    std::cout << "接收到客户端的数据：" << buffer << std::endl;
    std::string res_msg = "Hello, client!";

    // 发送消息
    if (write(client_sock, res_msg.c_str(), res_msg.size()) == -1) // 修改：使用client_sock而不是listen_sock
    {
        std::cout << "write error" << std::endl;
        return -1;
    }

    // 6.关闭套接字
    close(client_sock);
    close(listen_sock);
    return 0;
}