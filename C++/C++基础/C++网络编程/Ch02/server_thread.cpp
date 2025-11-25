#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <signal.h>
#include <thread> // 添加线程支持

// 全局变量，用于信号处理和线程控制
bool running = true;
int listen_sock = -1;
int client_sock = -1;

// 信号处理函数
void signalHandler(int signum)
{
    std::cout << "\n收到终止信号，正在关闭服务器..." << std::endl;
    running = false;

    // 关闭套接字
    if (client_sock != -1)
    {
        close(client_sock);
        std::cout << "客户端连接已关闭" << std::endl;
    }
    if (listen_sock != -1)
    {
        close(listen_sock);
        std::cout << "监听套接字已关闭" << std::endl;
    }

    exit(0);
}

// 发送消息线程函数
void sendMessageThread()
{
    while (running)
    {
        std::string res_msg;
        std::cout << "服务器回复: " << std::flush;
        std::getline(std::cin, res_msg);

        if (!running)
            break; // 检查是否应该退出

        if (write(client_sock, res_msg.c_str(), res_msg.size()) == -1)
        {
            std::cout << "write error" << std::endl;
            running = false;
            break;
        }
    }
}

// 接收消息线程函数
void receiveMessageThread()
{
    while (running)
    {
        char buffer[1024] = {0};
        int read_size = read(client_sock, buffer, sizeof(buffer) - 1);

        if (read_size == -1)
        {
            std::cout << "read error" << std::endl;
            running = false;
            break;
        }
        else if (read_size == 0)
        {
            std::cout << "客户端已关闭连接" << std::endl;
            running = false;
            break;
        }

        buffer[read_size] = '\0';
        std::cout << "\r客户端: " << buffer << std::endl;
        std::cout << "服务器回复: " << std::flush; // 重新显示输入提示
    }
}

int main(int, char **)
{
    // 注册信号处理函数
    signal(SIGINT, signalHandler);

    // 1.创建一个套接字
    listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock == -1)
    {
        std::cout << "socket create error" << std::endl;
        return -1;
    }

    // 设置套接字选项，允许端口复用
    int opt = 1;
    setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 2.绑定IP地址信息和端口号
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(6666);

    if (bind(listen_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        std::cout << "bind error" << std::endl;
        close(listen_sock);
        return -1;
    }

    // 3.监听套接字
    if (listen(listen_sock, 5) == -1)
    {
        std::cout << "listen error" << std::endl;
        close(listen_sock);
        return -1;
    }

    std::cout << "服务器启动成功，等待客户端连接... (按Ctrl+C退出)" << std::endl;

    // 4.接受客户端连接
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    client_sock = accept(listen_sock, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_sock == -1)
    {
        std::cout << "accept error" << std::endl;
        close(listen_sock);
        return -1;
    }

    std::cout << "客户端已连接，IP: " << inet_ntoa(client_addr.sin_addr)
              << ", 端口: " << ntohs(client_addr.sin_port) << std::endl;
    std::cout << "服务器回复: " << std::flush;

    // 创建并启动发送和接收线程
    std::thread send_thread(sendMessageThread);
    std::thread recv_thread(receiveMessageThread);

    // 等待线程结束
    if (send_thread.joinable())
        send_thread.join();
    if (recv_thread.joinable())
        recv_thread.join();

    // 6.关闭套接字
    if (client_sock != -1)
    {
        close(client_sock);
    }
    if (listen_sock != -1)
    {
        close(listen_sock);
    }

    std::cout << "服务器已关闭" << std::endl;
    return 0;
}