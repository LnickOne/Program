#include <iostream>
#include <string>
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HttpContext.h"

// 测试HTTP请求解析
void testHttpRequest() {
    std::cout << "=== Testing HttpRequest Parsing ===\n";
    
    // 模拟一个HTTP GET请求
    std::string request_str = 
        "GET /index.html HTTP/1.1\r\n"
        "Host: www.example.com\r\n"
        "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64)\r\n"
        "Accept: text/html,application/xhtml+xml\r\n"
        "Connection: keep-alive\r\n"
        "\r\n";
    
    HttpContext context;
    time_t now = time(NULL);
    
    if (context.parseRequest(const_cast<char*>(request_str.c_str()), request_str.size(), now)) {
        const HttpRequest& req = context.request();
        
        std::cout << "✓ Request parsed successfully\n";
        std::cout << "  Method: " << req.methodString() << "\n";
        std::cout << "  Path: " << req.path() << "\n";
        std::cout << "  Version: HTTP/" << (req.version() == HttpRequest::kHttp10 ? "1.0" : "1.1") << "\n";
        std::cout << "  Host: " << req.getHeader("Host") << "\n";
        std::cout << "  User-Agent: " << req.getHeader("User-Agent") << "\n";
    } else {
        std::cout << "✗ Request parsing failed\n";
    }
    
    std::cout << std::endl;
}

// 测试HTTP响应生成
void testHttpResponse() {
    std::cout << "=== Testing HttpResponse Generation ===\n";
    
    HttpResponse resp(false); // 不关闭连接
    resp.setStatusCode(HttpResponse::k200Ok);
    resp.setStatusMessage("OK");
    resp.setContentType("text/html; charset=utf-8");
    resp.addHeader("Server", "MyHttpServer/1.0");
    resp.addHeader("Content-Length", "123");
    resp.setBody("<html><head><title>Test</title></head><body><h1>Hello, World!</h1></body></html>");
    
    std::string output;
    resp.appendToBuffer(output);
    
    std::cout << "✓ Response generated successfully\n";
    std::cout << "Response:\n" << output << std::endl;
}

// 测试HTTP POST请求解析
void testHttpPostRequest() {
    std::cout << "=== Testing HTTP POST Request Parsing ===\n";
    
    // 模拟一个HTTP POST请求
    std::string request_str = 
        "POST /api/login HTTP/1.1\r\n"
        "Host: www.example.com\r\n"
        "Content-Type: application/x-www-form-urlencoded\r\n"
        "Content-Length: 27\r\n"
        "Connection: keep-alive\r\n"
        "\r\n"
        "username=test&password=123456";
    
    HttpContext context;
    time_t now = time(NULL);
    
    if (context.parseRequest(const_cast<char*>(request_str.c_str()), request_str.size(), now)) {
        const HttpRequest& req = context.request();
        
        std::cout << "✓ POST Request parsed successfully\n";
        std::cout << "  Method: " << req.methodString() << "\n";
        std::cout << "  Path: " << req.path() << "\n";
        std::cout << "  Content-Type: " << req.getHeader("Content-Type") << "\n";
        std::cout << "  Content-Length: " << req.getHeader("Content-Length") << "\n";
        
        // 注意：HttpRequest类默认不处理请求体，需要额外实现
        // 这里仅演示请求头的解析
    } else {
        std::cout << "✗ POST Request parsing failed\n";
    }
    
    std::cout << std::endl;
}

// 测试HttpContext状态管理
void testHttpContext() {
    std::cout << "=== Testing HttpContext State Management ===\n";
    
    HttpContext context;
    
    // 测试重置功能
    std::string partial_request = 
        "GET /index.html HTTP/1.1\r\n"
        "Host: www.example.com\r\n";
    
    time_t now = time(NULL);
    
    // 部分请求，解析应该失败
    if (!context.parseRequest(const_cast<char*>(partial_request.c_str()), partial_request.size(), now)) {
        std::cout << "✓ Partial request parsing correctly failed\n";
    }
    
    // 重置并重新测试
    context.reset();
    std::cout << "✓ HttpContext reset successfully\n";
    
    std::cout << std::endl;
}

int main() {
    std::cout << "HTTP Components Test Suite\n";
    std::cout << "================================\n\n";
    
    testHttpRequest();
    testHttpResponse();
    testHttpPostRequest();
    testHttpContext();
    
    std::cout << "================================\n";
    std::cout << "All tests completed!\n";
    
    return 0;
}