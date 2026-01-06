#include "HttpResponse.h"
#include <cstdio>
#include <string>
#include <unordered_map>
using namespace std;

// 状态码到状态消息的映射
const unordered_map<HttpResponse::HttpStatusCode, string> statusMessages = {
    {HttpResponse::kUnknown, "Unknown"},
    {HttpResponse::k200Ok, "OK"},
    {HttpResponse::k301MovedPermanently, "Moved Permanently"},
    {HttpResponse::k302Found, "Found"},
    {HttpResponse::k304NotModified, "Not Modified"},
    {HttpResponse::k400BadRequest, "Bad Request"},
    {HttpResponse::k401Unauthorized, "Unauthorized"},
    {HttpResponse::k403Forbidden, "Forbidden"},
    {HttpResponse::k404NotFound, "Not Found"},
    {HttpResponse::k405MethodNotAllowed, "Method Not Allowed"},
    {HttpResponse::k413PayloadTooLarge, "Payload Too Large"},
    {HttpResponse::k414UriTooLong, "URI Too Long"},
    {HttpResponse::k500InternalServerError, "Internal Server Error"},
    {HttpResponse::k501NotImplemented, "Not Implemented"},
    {HttpResponse::k503ServiceUnavailable, "Service Unavailable"},
};

/**
 * 设置HTTP状态码和默认状态消息
 */
void HttpResponse::setStatusCode(HttpStatusCode code)
{
    statusCode_ = code;
    auto it = statusMessages.find(code);
    if (it != statusMessages.end())
    {
        statusMessage_ = it->second;
    }
    else
    {
        statusMessage_ = "Unknown";
    }
}

/**
 * 将HTTP响应格式化为字符串
 */
void HttpResponse::appendToBuffer(string &output) const
{
    char buf[32];
    // 添加状态行
    snprintf(buf, sizeof buf, "HTTP/1.1 %d ", statusCode_);
    output.append(buf);
    output.append(statusMessage_);
    output.append("\r\n");

    // 添加响应头
    if (closeConnection_)
    {
        output.append("Connection: close\r\n");
    }
    else
    {
        snprintf(buf, sizeof buf, "Content-Length: %zd\r\n", body_.size());
        output.append(buf);
        output.append("Connection: Keep-Alive\r\n");
    }

    for (const auto &header : headers_)
    {
        output.append(header.first);
        output.append(": ");
        output.append(header.second);
        output.append("\r\n");
    }

    // 添加空行分隔响应头和响应体
    output.append("\r\n");
    // 添加响应体
    output.append(body_);
}