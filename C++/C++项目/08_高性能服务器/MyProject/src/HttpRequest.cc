#include "HttpRequest.h"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cassert>

using namespace std;

/**
 * 设置HTTP方法
 * @return 如果方法有效返回true，否则返回false
 */
bool HttpRequest::setMethod(const char *start, const char *end)
{
    assert(method_ == kInvalid);
    string m(start, end);
    if (m == "GET")
    {
        method_ = kGet;
        return true;
    }
    else if (m == "POST")
    {
        method_ = kPost;
        return true;
    }
    else if (m == "HEAD")
    {
        method_ = kHead;
        return true;
    }
    else if (m == "PUT")
    {
        method_ = kPut;
        return true;
    }
    else if (m == "DELETE")
    {
        method_ = kDelete;
        return true;
    }
    else
    {
        method_ = kInvalid;
        return false;
    }
}

/**
 * 获取HTTP方法的字符串表示
 */
const char *HttpRequest::methodString() const
{
    const char *result = "UNKNOWN";
    switch (method_)
    {
    case kGet:
        result = "GET";
        break;
    case kPost:
        result = "POST";
        break;
    case kHead:
        result = "HEAD";
        break;
    case kPut:
        result = "PUT";
        break;
    case kDelete:
        result = "DELETE";
        break;
    default:
        break;
    }
    return result;
}

/**
 * 设置HTTP版本
 */
void HttpRequest::setVersion(const char *start, const char *end)
{
    assert(version_ == kUnknown);
    string v(start, end);
    if (v == "HTTP/1.0")
    {
        version_ = kHttp10;
    }
    else if (v == "HTTP/1.1")
    {
        version_ = kHttp11;
    }
    else
    {
        version_ = kUnknown;
    }
}

/**
 * 添加HTTP头字段
 */
void HttpRequest::addHeader(const char *start, const char *colon, const char *end)
{
    string field(start, colon);
    ++colon;
    // 跳过冒号后的空白字符
    while (colon < end && isspace(*colon))
    {
        ++colon;
    }
    string value(colon, end);
    // 去掉值末尾的空白字符
    while (!value.empty() && isspace(value[value.size() - 1]))
    {
        value.resize(value.size() - 1);
    }
    headers_[field] = value;
}

/**
 * 添加HTTP头字段
 */
void HttpRequest::addHeader(const string &field, const string &value)
{
    headers_[field] = value;
}

/**
 * 交换两个HttpRequest对象的内容
 * @param other 另一个HttpRequest对象
 */
void HttpRequest::swap(HttpRequest &other)
{
    std::swap(method_, other.method_);
    std::swap(version_, other.version_);
    path_.swap(other.path_);
    query_.swap(other.query_);
    body_.swap(other.body_);
    std::swap(receiveTime_, other.receiveTime_);
    headers_.swap(other.headers_);
}

/**
 * 获取HTTP头字段
 */
string HttpRequest::getHeader(const string &field) const
{
    string result;
    auto it = headers_.find(field);
    if (it != headers_.end())
    {
        result = it->second;
    }
    return result;
}

/**
 * 解析HTTP请求行
 */
bool HttpRequest::parseRequestLine(const char *start, const char *end)
{
    bool succeed = false;
    const char *space = std::find(start, end, ' ');
    if (space != end && setMethod(start, space))
    {
        const char *startUri = space + 1;
        space = std::find(startUri, end, ' ');
        if (space != end)
        {
            const char *question = std::find(startUri, space, '?');
            if (question != space)
            {
                setPath(startUri, question);
                setQuery(question + 1, space);
            }
            else
            {
                setPath(startUri, space);
            }
            const char *startVersion = space + 1;
            if (end - startVersion == 8 && std::equal(startVersion, end - 1, "HTTP/1."))
            {
                if (*(end - 1) == '1')
                {
                    setVersion(kHttp11);
                }
                else if (*(end - 1) == '0')
                {
                    setVersion(kHttp10);
                }
                else
                {
                    return false;
                }
                succeed = true;
            }
        }
    }
    return succeed;
}

/**
 * 重置请求对象
 */
void HttpRequest::reset()
{
    method_ = kInvalid;
    version_ = kUnknown;
    path_.clear();
    query_.clear();
    body_.clear();
    receiveTime_ = 0;
    headers_.clear();
}