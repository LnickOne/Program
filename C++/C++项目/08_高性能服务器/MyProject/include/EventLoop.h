// Copyright 2024. All Rights Reserved.
// Author: xxx@xxx.com

#ifndef MY_PROJECT_EVENT_LOOP_H
#define MY_PROJECT_EVENT_LOOP_H

#include <functional>
#include <vector>
#include "noncopyable.h"

class Channel;
class EPollPoller;

/**
 * 事件循环类
 * 每个线程最多只能有一个EventLoop对象
 * 主线程和IO线程都可以创建EventLoop对象
 */
class EventLoop : noncopyable {
public:
    /**
     * 构造函数
     */
    EventLoop();

    /**
     * 析构函数
     */
    ~EventLoop();

    /**
     * 事件循环
     */
    void loop();

    /**
     * 退出事件循环
     */
    void quit();



    /**
     * 获取当前事件循环对象
     */
    static EventLoop* getEventLoopOfCurrentThread();

    /**
     * 更新事件通道
     * @param channel 事件通道
     */
    void updateChannel(Channel* channel);

    /**
     * 移除事件通道
     * @param channel 事件通道
     */
    void removeChannel(Channel* channel);

    /**
     * 检查事件通道是否在当前事件循环线程中
     * @param channel 事件通道
     */
    void assertInLoopThread() const;

    /**
     * 检查是否在当前事件循环线程中
     * @return 是否在当前事件循环线程中
     */
    bool isInLoopThread() const;
    
    /**
     * 检查事件通道是否在事件循环中
     * @param channel 事件通道
     * @return 是否在事件循环中
     */
    bool hasChannel(Channel* channel) const;

    /**
     * 在事件循环线程中执行任务
     * @param cb 任务回调函数
     */
    void runInLoop(const std::function<void()>& cb);

    /**
     * 在事件循环线程中执行任务
     * @param cb 任务回调函数
     */
    void queueInLoop(const std::function<void()>& cb);

private:
    /**
     * 唤醒事件循环
     */
    void wakeup();

    /**
     * 处理唤醒事件
     */
    void handleRead();

    /**
     * 执行待处理的任务
     */
    void doPendingFunctors();
    
    /**
     * 获取IO多路复用对象
     * @return IO多路复用对象
     */
    EPollPoller* poller() const { return poller_; }

    /**
     * 是否退出事件循环
     */
    bool looping_;

    /**
     * 是否退出事件循环
     */
    bool quit_;

    /**
     * 是否在处理待处理的任务
     */
    bool callingPendingFunctors_;



    /**
     * IO多路复用对象
     */
    EPollPoller* poller_;

    /**
     * 用于唤醒事件循环的文件描述符
     */
    int wakeupFd_;

    /**
     * 用于唤醒事件循环的事件通道
     */
    Channel* wakeupChannel_;

    /**
     * 待处理的任务队列
     */
    std::vector<std::function<void()>> pendingFunctors_;
};

#endif // MY_PROJECT_EVENT_LOOP_H