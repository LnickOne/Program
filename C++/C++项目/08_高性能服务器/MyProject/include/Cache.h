#ifndef MY_PROJECT_CACHE_H
#define MY_PROJECT_CACHE_H

#include "Timestamp.h"
#include <string>
#include <unordered_map>
#include <memory>
#include <mutex>

/**
 * 缓存条目类
 * 存储缓存的响应内容和相关信息
 */
class CacheEntry
{
public:
    /**
     * 构造函数
     * @param content 缓存的响应内容
     * @param contentType 内容类型
     * @param expireTime 过期时间戳
     */
    CacheEntry(const std::string& content, const std::string& contentType, Timestamp expireTime)
        : content_(content), contentType_(contentType), expireTime_(expireTime) {}

    /**
     * 获取缓存内容
     * @return 缓存的响应内容
     */
    const std::string& getContent() const { return content_; }

    /**
     * 获取内容类型
     * @return 内容类型
     */
    const std::string& getContentType() const { return contentType_; }

    /**
     * 获取过期时间
     * @return 过期时间戳
     */
    Timestamp getExpireTime() const { return expireTime_; }

    /**
     * 检查缓存是否过期
     * @return 是否过期
     */
    bool isExpired() const { return Timestamp::now() > expireTime_; }

private:
    std::string content_;      // 缓存的响应内容
    std::string contentType_;  // 内容类型
    Timestamp expireTime_;     // 过期时间
};

/**
 * 缓存管理器类
 * 管理缓存条目，提供线程安全的缓存操作
 */
class CacheManager
{
public:
    /**
     * 构造函数
     * @param defaultExpireTime 默认过期时间（秒）
     * @param maxSize 缓存最大条目数
     */
    CacheManager(int defaultExpireTime = 3600, size_t maxSize = 1000)
        : defaultExpireTime_(defaultExpireTime), maxSize_(maxSize) {}

    /**
     * 添加缓存条目
     * @param key 缓存键
     * @param content 缓存内容
     * @param contentType 内容类型
     * @param expireTime 过期时间（秒，可选，默认使用defaultExpireTime_）
     */
    void addCache(const std::string& key, const std::string& content, const std::string& contentType, int expireTime = -1);

    /**
     * 获取缓存条目
     * @param key 缓存键
     * @return 缓存条目共享指针，若不存在或已过期则返回nullptr
     */
    std::shared_ptr<CacheEntry> getCache(const std::string& key);

    /**
     * 删除缓存条目
     * @param key 缓存键
     */
    void removeCache(const std::string& key);

    /**
     * 清理过期缓存
     */
    void cleanupExpired();

    /**
     * 获取缓存大小
     * @return 缓存条目数
     */
    size_t size() const { return cacheMap_.size(); }

private:
    using CacheMap = std::unordered_map<std::string, std::shared_ptr<CacheEntry>>;
    CacheMap cacheMap_;                // 缓存映射表
    int defaultExpireTime_;            // 默认过期时间（秒）
    size_t maxSize_;                   // 缓存最大条目数
    mutable std::mutex mutex_;         // 互斥锁，保证线程安全
};

#endif // MY_PROJECT_CACHE_H