#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <atomic>

using namespace std;
using namespace chrono;

atomic<int> g_successCount(0);
atomic<int> g_failureCount(0);

void testClient(int port, int requestCount)
{
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        g_failureCount++;
        return;
    }

    if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("connect");
        close(sockfd);
        g_failureCount++;
        return;
    }

    // 发送HTTP请求
    const char* request = "GET / HTTP/1.1\r\nHost: localhost\r\nConnection: keep-alive\r\n\r\n";
    const int requestLen = strlen(request);

    char buffer[4096];

    for (int i = 0; i < requestCount; ++i)
    {
        int ret = send(sockfd, request, requestLen, 0);
        if (ret != requestLen)
        {
            g_failureCount++;
            continue;
        }

        // 接收响应
        int bytesRead = 0;
        bool gotResponse = false;
        while ((bytesRead = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0)
        {
            buffer[bytesRead] = '\0';
            if (strstr(buffer, "HTTP/1.1 200") != nullptr)
            {
                g_successCount++;
                gotResponse = true;
                break;
            }
        }

        if (!gotResponse)
        {
            g_failureCount++;
        }
    }

    close(sockfd);
}

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        cerr << "Usage: " << argv[0] << " <port> <client_count> <request_per_client>" << endl;
        return 1;
    }

    int port = stoi(argv[1]);
    int clientCount = stoi(argv[2]);
    int requestPerClient = stoi(argv[3]);

    cout << "Starting performance test..." << endl;
    cout << "Port: " << port << endl;
    cout << "Number of clients: " << clientCount << endl;
    cout << "Requests per client: " << requestPerClient << endl;
    cout << "Total requests: " << clientCount * requestPerClient << endl;
    cout << "" << endl;

    auto startTime = high_resolution_clock::now();

    vector<thread> clients;
    for (int i = 0; i < clientCount; ++i)
    {
        clients.emplace_back(testClient, port, requestPerClient);
        // 错开启动时间，避免瞬间连接风暴
        this_thread::sleep_for(milliseconds(10));
    }

    // 等待所有客户端完成
    for (auto& client : clients)
    {
        if (client.joinable())
        {
            client.join();
        }
    }

    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(endTime - startTime).count();
    double seconds = duration / 1000.0;

    cout << "" << endl;
    cout << "Test completed!" << endl;
    cout << "Duration: " << duration << " ms (" << seconds << " s)" << endl;
    cout << "Successful requests: " << g_successCount << endl;
    cout << "Failed requests: " << g_failureCount << endl;
    cout << "Total requests: " << (g_successCount + g_failureCount) << endl;
    cout << "Requests per second: " << static_cast<double>(g_successCount) / seconds << endl;
    cout << "Average response time per request: " << static_cast<double>(duration) / (g_successCount + g_failureCount) << " ms" << endl;

    return 0;
}