#include "HttpContext.h"
#include "HttpRequest.h"
#include <algorithm>
#include <cassert>
#include <string.h>
#include <time.h>
#include <cctype>
#include <string>

using namespace std;

/**
 * 解析请求行
 */
bool HttpContext::processRequestLine(const char *begin, const char *end)
{
    bool succeed = false;
    const char *start = begin;
    // 找到第一个空格（方法和路径之间）
    const char *space = std::find(start, end, ' ');
    if (space != end && request_.setMethod(start, space))
    {
        start = space + 1;
        // 找到第二个空格（路径和版本之间）
        space = std::find(start, end, ' ');
        if (space != end)
        {
            // 检查是否有查询字符串
            const char *question = std::find(start, space, '?');
            if (question != space)
            {
                request_.setPath(start, question);
                request_.setQuery(question + 1, space);
            }
            else
            {
                request_.setPath(start, space);
            }
            start = space + 1;
            // 检查HTTP版本
            succeed = end - start == 8 && std::equal(start, end - 1, "HTTP/1.");
            if (succeed)
            {
                if (*(end - 1) == '1')
                {
                    request_.setVersion(HttpRequest::kHttp11);
                }
                else if (*(end - 1) == '0')
                {
                    request_.setVersion(HttpRequest::kHttp10);
                }
                else
                {
                    succeed = false;
                }
            }
        }
    }
    return succeed;
}

/**
 * 解析HTTP请求数据
 */
bool HttpContext::parseRequest(char *buf, int len, time_t receiveTime)
{
    bool ok = true;
    bool hasMore = true;
    int pos = 0;
    request_.setReceiveTime(receiveTime);

    while (hasMore && pos < len && ok)
    {
        switch (state_)
        {
        case kExpectRequestLine:
        {
            // 查找请求行结束标志（\r\n）
            const char *crlf = strstr(buf + pos, "\r\n");
            if (crlf)
            {
                // 解析请求行
                ok = processRequestLine(buf + pos, crlf);
                if (ok)
                {
                    pos = crlf - buf + 2;
                    // 进入解析请求头状态
                    state_ = kExpectHeaders;
                }
                else
                {
                    hasMore = false;
                }
            }
            else
            {
                hasMore = false;
            }
            break;
        }
        case kExpectHeaders:
        {
            // 查找头字段结束标志（\r\n）
            const char *crlf = strstr(buf + pos, "\r\n");
            if (crlf)
            {
                // 查找冒号分隔符
                const char *colon = std::find<const char *>(buf + pos, crlf, ':');
                if (colon != crlf)
                {
                    // 解析头字段
                    std::string field(buf + pos, colon - (buf + pos));
                    ++colon;
                    // 跳过冒号后的空格
                    while (colon < crlf && isspace(static_cast<unsigned char>(*colon)))
                    {
                        ++colon;
                    }
                    std::string value(colon, crlf - colon);
                    // 去除值末尾的空格
                    while (!value.empty() && isspace(static_cast<unsigned char>(value[value.size() - 1])))
                    {
                        value.resize(value.size() - 1);
                    }
                    request_.addHeader(field, value);
                }
                else
                {
                    // 遇到空行，请求头结束
                    // 检查请求头中的Content-Length和Transfer-Encoding
                    std::string contentLength = request_.getHeader("Content-Length");
                    if (!contentLength.empty())
                    {
                        contentLength_ = std::stoi(contentLength);
                        if (contentLength_ > 0)
                        {
                            state_ = kExpectBody;
                            remainingBodyLen_ = contentLength_;
                        }
                        else
                        {
                            state_ = kGotAll;
                            hasMore = false;
                        }
                    }
                    else if (request_.getHeader("Transfer-Encoding") == "chunked")
                    {
                        chunked_ = true;
                        state_ = kExpectChunkLen;
                    }
                    else
                    {
                        // 没有请求体
                        state_ = kGotAll;
                        hasMore = false;
                    }
                }
                pos = crlf - buf + 2;
            }
            else
            {
                hasMore = false;
            }
            break;
        }
        case kExpectBody:
        {
            ok = processBodyContentLength(buf, len, pos);
            if (state_ == kGotAll)
            {
                hasMore = false;
            }
            break;
        }
        case kExpectChunkLen:
        {
            const char *crlf = strstr(buf + pos, "\r\n");
            if (crlf)
            {
                // 解析分块长度
                char *endptr;
                currentChunkLen_ = strtol(buf + pos, &endptr, 16);
                if (endptr > buf + pos && *endptr == '\r')
                {
                    if (currentChunkLen_ == 0)
                    {
                        // 最后一个分块
                        state_ = kExpectChunkEnd;
                    }
                    else
                    {
                        state_ = kExpectChunkData;
                        remainingBodyLen_ = currentChunkLen_;
                    }
                    pos = crlf - buf + 2;
                }
                else
                {
                    ok = false;
                    hasMore = false;
                }
            }
            else
            {
                hasMore = false;
            }
            break;
        }
        case kExpectChunkData:
        {
            ok = processBodyChunked(buf, len, pos);
            if (state_ == kExpectChunkEnd)
            {
                // 分块数据结束，等待分块结束标记
            }
            break;
        }
        case kExpectChunkEnd:
        {
            // 查找分块结束标记（\r\n）
            const char *crlf = strstr(buf + pos, "\r\n");
            if (crlf)
            {
                pos = crlf - buf + 2;
                // 所有分块都已解析完成
                state_ = kGotAll;
                hasMore = false;
            }
            else
            {
                hasMore = false;
            }
            break;
        }
        default:
        {
            hasMore = false;
            break;
        }
        }
    }
    return ok;
}

/**
 * 解析Content-Length请求体
 */
bool HttpContext::processBodyContentLength(const char *buf, int len, int &pos)
{
    if (pos >= len)
    {
        return true;
    }

    int available = len - pos;
    if (available < remainingBodyLen_)
    {
        // 数据不足，全部读取
        request_.body().append(buf + pos, available);
        remainingBodyLen_ -= available;
        pos = len;
        return true;
    }
    else
    {
        // 数据足够，读取剩余部分
        request_.body().append(buf + pos, remainingBodyLen_);
        pos += remainingBodyLen_;
        state_ = kGotAll;
        return true;
    }
}

/**
 * 解析Chunked编码请求体
 */
bool HttpContext::processBodyChunked(const char *buf, int len, int &pos)
{
    if (pos >= len)
    {
        return true;
    }

    int available = len - pos;
    if (available < remainingBodyLen_)
    {
        // 数据不足，全部读取
        request_.body().append(buf + pos, available);
        remainingBodyLen_ -= available;
        pos = len;
        return true;
    }
    else
    {
        // 数据足够，读取分块数据
        request_.body().append(buf + pos, remainingBodyLen_);
        pos += remainingBodyLen_;

        // 跳过分块数据后的\r\n
        const char *crlf = strstr(buf + pos, "\r\n");
        if (crlf)
        {
            pos = crlf - buf + 2;
            state_ = kExpectChunkLen;
        }
        else
        {
            // 等待完整的分块结束标记
            return false;
        }
        return true;
    }
}