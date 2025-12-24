#ifndef MY_PROJECT_HTTP_REQUEST_H
#define MY_PROJECT_HTTP_REQUEST_H

#include <string>
#include <unordered_map>
#include <vector>

/**
 * HTTP请求类
 * 用于解析和存储HTTP请求信息
 */
class HttpRequest
{
public:
    /**
     * HTTP方法枚举
     */
enum Method
    {
        kInvalid, kGet, kPost, kHead, kPut, kDelete
    };

    /**
     * HTTP版本枚举
     */
enum Version
    {
        kUnknown, kHttp10, kHttp11
    };

    /**
     * 构造函数
     */
    HttpRequest() : method_(kInvalid), version_(kUnknown) {}

    /**
     * 设置HTTP方法
     * @param start 方法字符串起始位置
     * @param end 方法字符串结束位置
     * @return 如果方法有效返回true，否则返回false
     */
    bool setMethod(const char* start, const char* end);

    /**
     * 获取HTTP方法
     * @return HTTP方法
     */
    Method method() const { return method_; }

    /**
     * 获取HTTP方法的字符串表示
     * @return 方法字符串
     */
    const char* methodString() const;

    /**
     * 设置HTTP版本
     * @param start 版本字符串起始位置
     * @param end 版本字符串结束位置
     */
    void setVersion(const char* start, const char* end);
    
    /**
     * 设置HTTP版本
     * @param v 版本枚举值
     */
    void setVersion(Version v) { version_ = v; }
    
    /**
     * 交换两个HttpRequest对象的内容
     * @param other 另一个HttpRequest对象
     */
    void swap(HttpRequest& other);

    /**
     * 获取HTTP版本
     * @return HTTP版本
     */
    Version version() const { return version_; }

    /**
     * 设置URL
     * @param start URL字符串起始位置
     * @param end URL字符串结束位置
     */
    void setPath(const char* start, const char* end) { path_.assign(start, end); }

    /**
     * 获取URL
     * @return URL字符串
     */
    const std::string& path() const { return path_; }

    /**
     * 设置查询字符串
     * @param start 查询字符串起始位置
     * @param end 查询字符串结束位置
     */
    void setQuery(const char* start, const char* end) { query_.assign(start, end); }

    /**
     * 获取查询字符串
     * @return 查询字符串
     */
    const std::string& query() const { return query_; }

    /**
     * 设置接收时间
     * @param t 时间戳
     */
    void setReceiveTime(time_t t) { receiveTime_ = t; }

    /**
     * 获取接收时间
     * @return 时间戳
     */
    time_t receiveTime() const { return receiveTime_; }

    /**
     * 添加HTTP头
     * @param start 头字段名起始位置
     * @param colon 冒号位置
     * @param end 头字段值结束位置
     */
    void addHeader(const char* start, const char* colon, const char* end);

    /**
     * 添加HTTP头
     * @param field 头字段名
     * @param value 头字段值
     */
    void addHeader(const std::string& field, const std::string& value);

    /**
     * 获取HTTP头
     * @param field 头字段名
     * @return 头字段值，如果不存在返回空字符串
     */
    std::string getHeader(const std::string& field) const;

    /**
     * 获取所有HTTP头
     * @return 头字段映射表
     */
    const std::unordered_map<std::string, std::string>& headers() const { return headers_; }

    /**
     * 解析HTTP请求行
     * @param start 数据起始位置
     * @param end 数据结束位置
     * @return 解析是否成功
     */
    bool parseRequestLine(const char* start, const char* end);

    /**
     * 重置请求对象
     */
    void reset();

    /**
     * 设置请求体
     * @param body 请求体内容
     */
    void setBody(const std::string& body) { body_ = body; }

    /**
     * 获取请求体
     * @return 请求体内容
     */
    const std::string& body() const { return body_; }

    /**
     * 获取可修改的请求体
     * @return 请求体内容
     */
    std::string& body() { return body_; }

private:
    Method method_;               // HTTP方法
    Version version_;             // HTTP版本
    std::string path_;            // URL路径
    std::string query_;           // 查询字符串
    time_t receiveTime_;          // 请求接收时间
    std::unordered_map<std::string, std::string> headers_;  // HTTP头字段
    std::string body_;            // 请求体内容
};

#endif // MY_PROJECT_HTTP_REQUEST_H