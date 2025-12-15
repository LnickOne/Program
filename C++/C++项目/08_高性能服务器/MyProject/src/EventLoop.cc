#include "EventLoop.h"
#include "Channel.h"
#include "EPollPoller.h"
#include "Logger.h"
#include "Timestamp.h"

#include <sys/types.h>
#include <sys/eventfd.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring>
#include <memory>
#include <functional>
#include <iostream>
#include <cassert>

/**
 * 定义线程本地存储的事件循环指针
 */
__thread EventLoop *t_loopInThisThread = nullptr;

/**
 * 获取当前线程ID
 */
pid_t gettid()
{
    return static_cast<pid_t>(::syscall(SYS_gettid));
}

/**
 * 创建eventfd用于线程间通信
 */
int createEventfd()
{
    int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (evtfd < 0)
    {
        LOG_FATAL << "Failed in eventfd: " << strerror(errno);
    }
    return evtfd;
}

/**
 * 事件循环构造函数
 */
EventLoop::EventLoop()
    : looping_(false),
      quit_(false),
      callingPendingFunctors_(false),
      poller_(new EPollPoller(this)),
      wakeupFd_(createEventfd()),
      wakeupChannel_(new Channel(this, wakeupFd_))
{
    LOG_DEBUG << "EventLoop " << this << " created";

    if (t_loopInThisThread)
    {
        LOG_FATAL << "Another EventLoop " << t_loopInThisThread
                  << " exists in this thread";
    }
    else
    {
        t_loopInThisThread = this;
    }

    // 设置唤醒通道的事件和回调
    wakeupChannel_->setReadCallback(
        std::bind(&EventLoop::handleRead, this));
    wakeupChannel_->enableReading();
}

/**
 * 事件循环析构函数
 */
EventLoop::~EventLoop()
{
    wakeupChannel_->disableAll();
    wakeupChannel_->remove();
    ::close(wakeupFd_);
    t_loopInThisThread = nullptr;
}

/**
 * 事件循环
 */
void EventLoop::loop()
{
    assert(!looping_);
    assertInLoopThread();
    looping_ = true;
    quit_ = false;

    LOG_DEBUG << "EventLoop " << this << " start looping";

    while (!quit_)
    {
        // 清空活跃事件通道列表
        std::vector<Channel *> activeChannels;
        // 等待事件发生
        Timestamp pollReturnTime = poller_->poll(1000, &activeChannels);

        // 处理活跃事件
        for (Channel *channel : activeChannels)
        {
            channel->handleEvent(pollReturnTime);
        }

        // 执行待处理的任务
        doPendingFunctors();
    }

    LOG_DEBUG << "EventLoop " << this << " stop looping";
    looping_ = false;
}

/**
 * 退出事件循环
 */
void EventLoop::quit()
{
    quit_ = true;
    if (!isInLoopThread())
    {
        wakeup();
    }
}

/**
 * 更新事件通道
 */
void EventLoop::updateChannel(Channel *channel)
{
    assert(channel->ownerLoop() == this);
    assertInLoopThread();
    poller_->updateChannel(channel);
}

/**
 * 移除事件通道
 */
void EventLoop::removeChannel(Channel *channel)
{
    assert(channel->ownerLoop() == this);
    assertInLoopThread();
    poller_->removeChannel(channel);
}

/**
 * 检查事件通道是否在当前事件循环线程中
 */
void EventLoop::assertInLoopThread() const
{
    if (!isInLoopThread())
    {
        LOG_FATAL << "EventLoop::assertInLoopThread - EventLoop " << this
                  << " is called in wrong thread";
    }
}

/**
 * 检查是否在当前事件循环线程中
 */
bool EventLoop::isInLoopThread() const
{
    return t_loopInThisThread == this;
}

/**
 * 检查事件通道是否在事件循环中
 */
bool EventLoop::hasChannel(Channel *channel) const
{
    assert(channel->ownerLoop() == this);
    return poller_->hasChannel(channel);
}

/**
 * 在事件循环线程中执行任务
 */
void EventLoop::runInLoop(const std::function<void()> &cb)
{
    if (isInLoopThread())
    {
        cb();
    }
    else
    {
        queueInLoop(cb);
    }
}

/**
 * 在事件循环线程中执行任务
 */
void EventLoop::queueInLoop(const std::function<void()> &cb)
{
    {
        // 这里应该加锁保护pendingFunctors_
        // 为了简化实现，暂时不加锁
        pendingFunctors_.push_back(cb);
    }

    if (!isInLoopThread() || callingPendingFunctors_)
    {
        wakeup();
    }
}

/**
 * 唤醒事件循环
 */
void EventLoop::wakeup()
{
    uint64_t one = 1;
    ssize_t n = ::write(wakeupFd_, &one, sizeof one);
    if (n != sizeof one)
    {
        LOG_ERROR << "EventLoop::wakeup() writes " << n << " bytes instead of 8";
    }
}

/**
 * 处理唤醒事件
 */
void EventLoop::handleRead()
{
    uint64_t one = 1;
    ssize_t n = ::read(wakeupFd_, &one, sizeof one);
    if (n != sizeof one)
    {
        LOG_ERROR << "EventLoop::handleRead() reads " << n << " bytes instead of 8";
    }
}

/**
 * 执行待处理的任务
 */
void EventLoop::doPendingFunctors()
{
    std::vector<std::function<void()>> functors;
    callingPendingFunctors_ = true;

    {
        // 这里应该加锁保护pendingFunctors_
        // 为了简化实现，暂时不加锁
        functors.swap(pendingFunctors_);
    }

    for (const auto &functor : functors)
    {
        functor();
    }

    callingPendingFunctors_ = false;
}

/**
 * 获取当前事件循环对象
 */
EventLoop *EventLoop::getEventLoopOfCurrentThread()
{
    return t_loopInThisThread;
}