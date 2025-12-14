// Copyright 2024. All Rights Reserved.
// Author: xxx@xxx.com

#ifndef MY_PROJECT_EPOLL_POLLER_H
#define MY_PROJECT_EPOLL_POLLER_H

#include <vector>
#include "Poller.h"

struct epoll_event;

/**
 * epoll的具体实现
 * 继承自Poller类
 */
class EPollPoller : public Poller {
public:
    /**
     * 构造函数
     * @param loop 所属的EventLoop
     */
    explicit EPollPoller(EventLoop* loop);

    /**
     * 析构函数
     */
    ~EPollPoller() override;

    /**
     * 等待事件发生
     * @param timeoutMs 超时时间（毫秒）
     * @param activeChannels 活跃的事件通道列表
     * @return 事件发生的时间
     */
    Timestamp poll(int timeoutMs, ChannelList* activeChannels) override;

    /**
     * 更新事件通道
     * @param channel 事件通道
     */
    void updateChannel(Channel* channel) override;

    /**
     * 移除事件通道
     * @param channel 事件通道
     */
    void removeChannel(Channel* channel) override;

private:
    /**
     * 最大的事件数
     */
    static const int kInitEventListSize = 16;

    /**
     * 填写活跃的事件通道列表
     * @param numEvents 事件数
     * @param activeChannels 活跃的事件通道列表
     */
    void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

    /**
     * 更新事件通道的操作
     * @param operation 操作类型
     * @param channel 事件通道
     */
    void update(int operation, Channel* channel);

    /**
     * epoll文件描述符
     */
    int epollfd_;

    /**
     * epoll事件列表
     */
    std::vector<struct epoll_event> events_;
};

#endif // MY_PROJECT_EPOLL_POLLER_H