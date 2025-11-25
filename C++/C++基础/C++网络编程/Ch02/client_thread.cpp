#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <thread> // 添加线程支持

// 全局变量，用于信号处理和线程控制
bool running = true;
int client_sock = -1;

// 信号处理函数
void signalHandler(int signum)
{
    std::cout << "\n收到终止信号，正在关闭客户端..." << std::endl;
    running = false;

    // 关闭套接字
    if (client_sock != -1)
    {
        close(client_sock);
        std::cout << "连接已关闭" << std::endl;
    }

    exit(0);
}

// 发送消息线程函数
void sendMessageThread()
{
    while (running)
    {
        std::string msg;
        std::cout << "客户端发送: " << std::flush;
        std::getline(std::cin, msg);

        if (!running)
            break; // 检查是否应该退出

        if (msg.empty())
        {
            continue; // 跳过空消息
        }

        if (write(client_sock, msg.c_str(), msg.size()) == -1)
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
            std::cout << "服务器已关闭连接" << std::endl;
            running = false;
            break;
        }

        buffer[read_size] = '\0';
        std::cout << "\r服务器: " << buffer << std::endl;
        std::cout << "客户端发送: " << std::flush; // 重新显示输入提示
    }
}

int main()
{
    // 注册信号处理函数
    signal(SIGINT, signalHandler);

    // 1.创建一个套接字socket
    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock == -1)
    {
        std::cout << "socket create error" << std::endl;
        return -1;
    }

    // 2.连接服务器
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr.s_addr);
    server_addr.sin_port = htons(6666);

    if (connect(client_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        std::cout << "connect error" << std::endl;
        close(client_sock);
        return -1;
    }

    std::cout << "连接服务器成功 (按Ctrl+C退出)" << std::endl;
    std::cout << "客户端发送: " << std::flush;

    // 创建并启动发送和接收线程
    std::thread send_thread(sendMessageThread);
    std::thread recv_thread(receiveMessageThread);

    // 等待线程结束
    if (send_thread.joinable())
        send_thread.join();
    if (recv_thread.joinable())
        recv_thread.join();

    // 4.关闭套接字
    if (client_sock != -1)
    {
        close(client_sock);
    }

    std::cout << "客户端已关闭" << std::endl;
    return 0;
}