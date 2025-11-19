#include <string>
#include <TcpServer.h>
#include <Logger.h>
#include <sys/stat.h>
#include <sstream>
#include "AsyncLogging.h"
#include "LFU.h"
#include "memoryPool.h"
/*
static 的作用（文件作用域内部链接）：
仅在 main.cc 这个编译单元内可见，避免导出全局符号与其他文件同名冲突。
保证该常量的存储期为整个进程（程序运行期），符合“配置常量”的使用场景。
const 的作用（只读常量）：
表达语义：日志滚动阈值是配置常量，不应被修改。
允许编译器优化，通常放入只读段，防止意外改写。
额外建议：
若值在编译期已知，可用 constexpr 明确常量表达式，例如：
    constexpr off_t kRollSize = 1 * 1024 * 1024;
或用无符号更贴合字节大小：constexpr size_t kRollSize = 1u * 1024 * 1024;
若需跨文件共享，改为放在头文件的 inline constexpr（C++17+）或在头文件声明、源文件定义（去掉 static）。
*/
static const off_t kRollSize = 1 * 1024 * 1024; // 日志文件滚动大小为1MB (1*1024*1024字节)
class EchoServer
{
public:
    EchoServer(EventLoop *loop, const InetAddress &addr, const std::string &name) : server_(loop, addr, name), loop_(loop)
    {
        // 注册回调函数
        server_.setConnectionCallback(std::bind(&EchoServer::onConnection, this, std::placeholders::_1));
        server_.setMessageCallback(std::bind(&EchoServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        // 设置合适的subloop线程数量
        server_.setThreadNum(3);
    }
    void start()
    {
        server_.start();
    }

private:
    // 连接建立或断开的回调函数
    void onConnection(const TcpConnectionPtr &conn)
    {
        if (conn->connected())
        {
            LOG_INFO << "Connection UP :" << conn->peerAddress().toIpPort().c_str();
        }
        else
        {
            LOG_INFO << "Connection DOWN :" << conn->peerAddress().toIpPort().c_str();
        }
    }
    // 可读写事件回调
    void onMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp time)
    {
        std::string msg = buf->retrieveAllAsString();
        conn->send(msg);
        // conn->shutdown();   // 关闭写端 底层响应EPOLLHUP => 执行closeCallback_
    }
    TcpServer server_;
    EventLoop *loop_;
};
AsyncLogging *g_asyncLog = NULL;
AsyncLogging *getAsyncLog()
{
    return g_asyncLog;
}
void asyncLog(const char *msg, int len)
{
    AsyncLogging *logging = getAsyncLog();
    if (logging)
    {
        logging->append(msg, len);
    }
}
int main(int argc, char *argv[])
{
    // 第一步启动日志，双缓冲异步写入磁盘.
    // 创建一个文件夹
    const std::string LogDir = "logs";
    mkdir(LogDir.c_str(), 0755);
    // 使用std::stringstream 构建日志文件夹
    std::ostringstream LogfilePath;
    LogfilePath << LogDir << "/" << ::basename(argv[0]); // 完整的日志文件路径
    AsyncLogging log(LogfilePath.str(), kRollSize);
    g_asyncLog = &log;
    Logger::setOutput(asyncLog); // 为Logger设置输出回调, 重新配接输出位置
    log.start();                 // 开启日志后端线程
    // 第二步启动内存池和LFU缓存
    // 初始化内存池
    memoryPool::HashBucket::initMemoryPool();

    // 初始化缓存
    const int CAPACITY = 5;
    KamaCache::KLfuCache<int, std::string> lfu(CAPACITY);
    // 第三步启动底层网络模块
    EventLoop loop;
    InetAddress addr(8080);
    EchoServer server(&loop, addr, "EchoServer");
    server.start();
    // 主loop开始事件循环  epoll_wait阻塞
    // 等待就绪事件(主loop只注册了监听套接字的fd，所以只会处理新连接事件)
    std::cout << "=======================Start Web Server==========================" << std::endl;
    loop.loop();
    std::cout << "=======================Stop  Web Server==========================" << std::endl;
    // 结束日志打印
    log.stop();
}