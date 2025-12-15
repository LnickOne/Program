#ifndef MY_PROJECT_POLLER_H
#define MY_PROJECT_POLLER_H

#include <vector>
#include <map>
#include "noncopyable.h"
#include "Timestamp.h"

class Channel;
class EventLoop;

/**
 * IO多路复用的抽象基类
 * 封装了IO多路复用的通用接口
 */
class Poller : noncopyable
{
public:
    /**
     * 事件通道列表类型
     */
    using ChannelList = std::vector<Channel *>;

    /**
     * 构造函数
     * @param loop 所属的EventLoop
     */
    explicit Poller(EventLoop *loop);

    /**
     * 析构函数
     */
    virtual ~Poller();

    /**
     * 等待事件发生
     * @param timeoutMs 超时时间（毫秒）
     * @param activeChannels 活跃的事件通道列表
     * @return 事件发生的时间
     */
    virtual Timestamp poll(int timeoutMs, ChannelList *activeChannels) = 0;

    /**
     * 更新事件通道
     * @param channel 事件通道
     */
    virtual void updateChannel(Channel *channel) = 0;

    /**
     * 移除事件通道
     * @param channel 事件通道
     */
    virtual void removeChannel(Channel *channel) = 0;

    /**
     * 检查事件通道是否在Poller中
     * @param channel 事件通道
     * @return 是否在Poller中
     */
    virtual bool hasChannel(Channel *channel) const;

    /**
     * 创建默认的Poller
     * @param loop 所属的EventLoop
     * @return Poller指针
     */
    static Poller *newDefaultPoller(EventLoop *loop);

    /**
     * 断言是否在EventLoop线程中
     */
    void assertInLoopThread() const;

protected:
    /**
     * 事件通道映射表
     * fd -> Channel
     */
    using ChannelMap = std::map<int, Channel *>;
    ChannelMap channels_;

private:
    /**
     * 所属的EventLoop
     */
    EventLoop *ownerLoop_;
};

#endif // MY_PROJECT_POLLER_H