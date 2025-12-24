#ifndef MY_PROJECT_HTTP_CONTEXT_H
#define MY_PROJECT_HTTP_CONTEXT_H

#include "HttpRequest.h"

/**
 * HTTP上下文类
 * 用于解析HTTP请求的状态机
 */
class HttpContext
{
public:
    /**
     * 解析状态枚举
     */
enum HttpRequestParseState
    {
        kExpectRequestLine, // 期望解析请求行
        kExpectHeaders,     // 期望解析请求头
        kExpectBody,        // 期望解析请求体
        kExpectChunkLen,    // 期望解析分块长度
        kExpectChunkData,   // 期望解析分块数据
        kExpectChunkEnd,    // 期望解析分块结束标记
        kGotAll,            // 已获取完整请求
    };

    /**
     * 构造函数
     */
    HttpContext() : state_(kExpectRequestLine) {}

    /**
     * 解析请求数据
     * @param buf 输入缓冲区
     * @param len 数据长度
     * @param receiveTime 请求接收时间
     * @return 解析是否成功
     */
    bool parseRequest(char *buf, int len, time_t receiveTime);

    /**
     * 获取当前解析状态
     * @return 解析状态
     */
    bool gotAll() const { return state_ == kGotAll; }

    /**
     * 获取HTTP请求对象
     * @return HTTP请求对象
     */
    const HttpRequest &request() const { return request_; }

    /**
     * 获取可修改的HTTP请求对象
     * @return HTTP请求对象
     */
    HttpRequest &request() { return request_; }

    /**
     * 重置解析状态
     */
    void reset()
    {
        state_ = kExpectRequestLine;
        HttpRequest dummy;
        request_.swap(dummy);
    }

private:
    /**
     * 解析请求行
     * @param begin 数据起始位置
     * @param end 数据结束位置
     * @return 解析是否成功
     */
    bool processRequestLine(const char *begin, const char *end);
    
    /**
     * 解析Content-Length请求体
     * @param buf 数据缓冲区
     * @param len 数据长度
     * @param pos 当前解析位置
     * @return 解析是否成功
     */
    bool processBodyContentLength(const char *buf, int len, int &pos);
    
    /**
     * 解析Chunked编码请求体
     * @param buf 数据缓冲区
     * @param len 数据长度
     * @param pos 当前解析位置
     * @return 解析是否成功
     */
    bool processBodyChunked(const char *buf, int len, int &pos);

    HttpRequestParseState state_; // 当前解析状态
    HttpRequest request_;         // HTTP请求对象
    int contentLength_;           // 请求体长度（Content-Length）
    bool chunked_;                // 是否使用Chunked编码
    int currentChunkLen_;         // 当前分块长度
    int remainingBodyLen_;        // 剩余请求体长度
};

#endif // MY_PROJECT_HTTP_CONTEXT_H