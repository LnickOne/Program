#include "Cache.h"
#include <algorithm>

void CacheManager::moveToFront(const std::string& key, CacheMap::iterator it)
{
    // 从列表中移除当前位置
    keyList_.erase(it->second.second);
    // 添加到列表头部
    keyList_.push_front(key);
    // 更新映射表中的迭代器
    it->second.second = keyList_.begin();
}

void CacheManager::addCache(const std::string& key, const std::string& content, const std::string& contentType, int expireTime)
{
    std::lock_guard<std::mutex> lock(mutex_);

    // 检查键是否已经存在
    auto it = cacheMap_.find(key);
    if (it != cacheMap_.end())
    {
        // 键已存在，移动到LRU队列头部
        moveToFront(key, it);
        // 更新缓存内容和过期时间
        int expire = expireTime > 0 ? expireTime : defaultExpireTime_;
        Timestamp expireTimeStamp = addTime(Timestamp::now(), static_cast<double>(expire));
        it->second.first = std::make_shared<CacheEntry>(content, contentType, expireTimeStamp);
        return;
    }

    // 如果超过最大大小，删除最久未使用的条目
    if (cacheMap_.size() >= maxSize_ && !cacheMap_.empty())
    {
        // 删除LRU队列尾部的条目
        std::string lruKey = keyList_.back();
        keyList_.pop_back();
        cacheMap_.erase(lruKey);
    }

    // 计算过期时间
    int expire = expireTime > 0 ? expireTime : defaultExpireTime_;
    Timestamp expireTimeStamp = addTime(Timestamp::now(), static_cast<double>(expire));

    // 添加到LRU队列头部
    keyList_.push_front(key);
    // 添加到缓存映射表
    cacheMap_[key] = std::make_pair(
        std::make_shared<CacheEntry>(content, contentType, expireTimeStamp),
        keyList_.begin()
    );
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
    if (it->second.first->isExpired())
    {
        // 从LRU队列中移除
        keyList_.erase(it->second.second);
        // 从缓存映射表中移除
        cacheMap_.erase(it);
        return nullptr;
    }

    // 移动到LRU队列头部（最近使用）
    moveToFront(key, it);

    return it->second.first;
}

void CacheManager::removeCache(const std::string& key)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = cacheMap_.find(key);
    if (it != cacheMap_.end())
    {
        // 从LRU队列中移除
        keyList_.erase(it->second.second);
        // 从缓存映射表中移除
        cacheMap_.erase(it);
    }
}

void CacheManager::cleanupExpired()
{
    std::lock_guard<std::mutex> lock(mutex_);

    auto it = keyList_.begin();
    while (it != keyList_.end())
    {
        const std::string& key = *it;
        auto cacheIt = cacheMap_.find(key);
        
        if (cacheIt != cacheMap_.end() && cacheIt->second.first->isExpired())
        {
            // 缓存已过期，从LRU队列和映射表中移除
            cacheMap_.erase(cacheIt);
            it = keyList_.erase(it);
        }
        else
        {
            ++it;
        }
    }
}