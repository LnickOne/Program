#include "Cache.h"
#include <algorithm>

void CacheManager::addCache(const std::string& key, const std::string& content, const std::string& contentType, int expireTime)
{
    std::lock_guard<std::mutex> lock(mutex_);

    // 如果超过最大大小，删除一个条目（这里简单删除第一个）
    if (cacheMap_.size() >= maxSize_ && !cacheMap_.empty())
    {
        auto it = cacheMap_.begin();
        cacheMap_.erase(it);
    }

    // 计算过期时间
    int expire = expireTime > 0 ? expireTime : defaultExpireTime_;
    Timestamp expireTimeStamp = addTime(Timestamp::now(), static_cast<double>(expire));

    // 添加缓存条目
    cacheMap_[key] = std::make_shared<CacheEntry>(content, contentType, expireTimeStamp);
}

std::shared_ptr<CacheEntry> CacheManager::getCache(const std::string& key)
{
    std::lock_guard<std::mutex> lock(mutex_);

    auto it = cacheMap_.find(key);
    if (it == cacheMap_.end())
    {
        return nullptr;
    }

    // 检查缓存是否过期
    if (it->second->isExpired())
    {
        cacheMap_.erase(it);
        return nullptr;
    }

    return it->second;
}

void CacheManager::removeCache(const std::string& key)
{
    std::lock_guard<std::mutex> lock(mutex_);
    cacheMap_.erase(key);
}

void CacheManager::cleanupExpired()
{
    std::lock_guard<std::mutex> lock(mutex_);

    auto it = cacheMap_.begin();
    while (it != cacheMap_.end())
    {
        if (it->second->isExpired())
        {
            it = cacheMap_.erase(it);
        }
        else
        {
            ++it;
        }
    }
}