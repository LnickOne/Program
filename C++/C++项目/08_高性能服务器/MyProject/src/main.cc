#include <iostream>
#include "EventLoop.h"
#include "Logger.h"
#include "HttpServer.h"
#include "InetAddress.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include <string>

// HTTP请求处理函数
void onHttpRequest(const HttpRequest &req, HttpResponse *resp)
{
    LOG_INFO << "onHttpRequest(): " << req.methodString() << " " << req.path();

    // 设置响应状态码
    resp->setStatusCode(HttpResponse::k200Ok);
    resp->setStatusMessage("OK");

    // 设置响应头
    resp->setContentType("text/html; charset=utf-8");
    resp->addHeader("Server", "MyHttpServer");

    // 构造简单的HTML响应体
    std::string body;
    body += "<html><head><title>MyHttpServer</title></head>";
    body += "<body><h1>Hello, World!</h1>";
    body += "<p>Request path: " + req.path() + "</p>";
    body += "<p>Request method: " + std::string(req.methodString()) + "</p>";
    body += "</body></html>";

    resp->setBody(body);
}

int main()
{
    // 初始化日志系统
    setLogLevel(INFO);

    // 创建一个事件循环对象
    EventLoop loop;

    // 设置服务器监听地址和端口
    InetAddress listenAddr(8080);

    // 创建HTTP服务器实例
    HttpServer server(&loop, listenAddr, "MyHttpServer");

    // 设置HTTP请求处理回调函数
    server.setHttpCallback(onHttpRequest);

    // 设置静态文件根目录
    server.setStaticFileRoot("./static");

    // 设置线程数量（多线程处理）
    server.setThreadNum(4); // 使用4个IO线程

    // 启动服务器
    server.start();

    LOG_INFO << "MyHttpServer is running on port 8080...";

    // 运行事件循环
    loop.loop();

    return 0;
}