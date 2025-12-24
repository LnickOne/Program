#ifndef MY_PROJECT_HTTP_SERVER_H
#define MY_PROJECT_HTTP_SERVER_H

#include <memory>
#include <string>
#include <functional>
#include "TcpServer.h"
#include "TcpConnection.h"
#include "HttpContext.h"
#include "HttpResponse.h"
#include "noncopyable.h"
#include "Cache.h"

/**
 * HTTP服务器类
 * 基于TcpServer实现的HTTP服务器
 */
class HttpServer : noncopyable
{
public:
    /**
     * HTTP请求处理回调函数类型
     */
    typedef std::function<void(const HttpRequest &, HttpResponse *)> HttpCallback;

    /**
     * 构造函数
     * @param loop 事件循环
     * @param listenAddr 监听地址
     * @param name 服务器名称
     */
    HttpServer(EventLoop *loop,
               const InetAddress &listenAddr,
               const std::string &nameArg);

    /**
     * 析构函数
     */
    ~HttpServer();

    /**
     * 设置线程数量
     * @param numThreads 线程数量
     */
    void setThreadNum(int numThreads)
    {
        server_.setThreadNum(numThreads);
    }

    /**
     * 设置HTTP请求处理回调函数
     * @param cb 回调函数
     */
    void setHttpCallback(const HttpCallback &cb)
    {
        httpCallback_ = cb;
    }
    
    /**
     * 设置静态文件根目录
     * @param root 静态文件根目录
     */
    void setStaticFileRoot(const std::string &root)
    {
        staticFileRoot_ = root;
    }
    
    /**
     * 获取静态文件根目录
     * @return 静态文件根目录
     */
    const std::string &getStaticFileRoot() const
    {
        return staticFileRoot_;
    }

    /**
     * 启动服务器
     */
    void start();

private:
    /**
     * 连接建立回调函数
     * @param conn TCP连接
     */
    void onConnection(const std::shared_ptr<TcpConnection> &conn);

    /**
     * 消息到达回调函数
     * @param conn TCP连接
     * @param buf 输入缓冲区
     */
    void onMessage(const std::shared_ptr<TcpConnection> &conn, std::string &buf);

    /**
     * 处理HTTP请求
     * @param conn TCP连接
     * @param req HTTP请求
     */
    void onRequest(const std::shared_ptr<TcpConnection> &conn, const HttpRequest &req);
    
    /**
     * 处理静态文件请求
     * @param req HTTP请求
     * @param resp HTTP响应
     * @return 是否成功处理
     */
    bool handleStaticFile(const HttpRequest &req, HttpResponse *resp);
    
    /**
     * 根据文件扩展名获取Content-Type
     * @param path 文件路径
     * @return Content-Type字符串
     */
    std::string getContentTypeByExtension(const std::string &path);

    TcpServer server_;               // 底层TCP服务器
    HttpCallback httpCallback_;      // HTTP请求处理回调
    std::string staticFileRoot_;     // 静态文件根目录
    CacheManager cacheManager_;      // 缓存管理器
};

#endif // MY_PROJECT_HTTP_SERVER_H