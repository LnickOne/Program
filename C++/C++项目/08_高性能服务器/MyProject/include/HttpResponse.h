#ifndef MY_PROJECT_HTTP_RESPONSE_H
#define MY_PROJECT_HTTP_RESPONSE_H

#include <string>
#include <unordered_map>
#include <vector>
#include "noncopyable.h"

/**
 * HTTP响应类
 * 用于构建和存储HTTP响应信息
 */
class HttpResponse : noncopyable
{
public:
    /**
     * HTTP状态码枚举
     */
    enum HttpStatusCode
    {
        kUnknown,                      // 未知状态码
        k200Ok = 200,                  // OK
        k301MovedPermanently = 301,    // 永久重定向
        k302Found = 302,               // 临时重定向
        k304NotModified = 304,         // 未修改
        k400BadRequest = 400,          // 错误请求
        k401Unauthorized = 401,        // 未授权
        k403Forbidden = 403,           // 禁止访问
        k404NotFound = 404,            // 资源未找到
        k405MethodNotAllowed = 405,    // 方法不允许
        k413PayloadTooLarge = 413,     // 请求实体过大
        k414UriTooLong = 414,          // 请求URI过长
        k500InternalServerError = 500, // 服务器内部错误
        k501NotImplemented = 501,      // 未实现
        k503ServiceUnavailable = 503,  // 服务不可用
    };

    /**
     * 构造函数
     */
    explicit HttpResponse(bool close) : statusCode_(kUnknown), closeConnection_(close) {}

    /**
     * 设置HTTP状态码
     * @param code 状态码
     */
    void setStatusCode(HttpStatusCode code);

    /**
     * 设置状态描述
     * @param message 状态描述
     */
    void setStatusMessage(const std::string &message) { statusMessage_ = message; }

    /**
     * 设置是否关闭连接
     * @param on 是否关闭
     */
    void setCloseConnection(bool on) { closeConnection_ = on; }

    /**
     * 获取是否关闭连接
     * @return 是否关闭连接
     */
    bool closeConnection() const { return closeConnection_; }
    
    /**
     * 获取HTTP状态码
     * @return 状态码
     */
    HttpStatusCode getStatusCode() const { return statusCode_; }

    /**
     * 设置内容类型
     * @param contentType 内容类型
     */
    void setContentType(const std::string &contentType)
    {
        addHeader("Content-Type", contentType);
    }

    /**
     * 添加头字段
     * @param key 头字段名
     * @param value 头字段值
     */
    void addHeader(const std::string &key, const std::string &value)
    {
        headers_[key] = value;
    }

    /**
     * 设置响应正文
     * @param body 响应正文
     */
    void setBody(const std::string &body) { body_ = body; }

    /**
     * 获取响应正文
     * @return 响应正文
     */
    const std::string &getBody() const { return body_; }

    /**
     * 将HTTP响应格式化为字符串
     * @param output 输出缓冲区
     */
    void appendToBuffer(std::string &output) const;

private:
    std::unordered_map<std::string, std::string> headers_; // HTTP响应头
    HttpStatusCode statusCode_;                            // HTTP状态码
    std::string statusMessage_;                            // 状态描述
    bool closeConnection_;                                 // 是否关闭连接
    std::string body_;                                     // 响应正文
};

#endif // MY_PROJECT_HTTP_RESPONSE_H