// Copyright 2024. All Rights Reserved.
// Author: xxx@xxx.com

#include "EPollPoller.h"
#include "EventLoop.h"
#include "Channel.h"
#include "Logger.h"

#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <cassert>

// 定义Poller中使用的索引常量
enum {
    kNew = -1,    // 新添加的通道
    kAdded = 1,   // 已添加到epoll中的通道
    kDeleted = 2  // 已从epoll中删除的通道
};

// 简单的类型转换模板
template<typename To, typename From>
inline To implicit_cast(From const &f) {
    return f;
}

/**
 * 错误信息转换函数
 */
static const char* operationToString(int op) {
    switch (op) {
    case EPOLL_CTL_ADD: return "ADD";
    case EPOLL_CTL_DEL: return "DEL";
    case EPOLL_CTL_MOD: return "MOD";
    default: return "UNKNOWN";
    }
}

/**
 * 创建一个非阻塞的文件描述符
 */
static int createEpollfd() {
    int epollfd = ::epoll_create1(EPOLL_CLOEXEC);
    if (epollfd < 0) {
        LOG_FATAL << "Failed in epoll_create1: " << strerror(errno);
    }
    return epollfd;
}

/**
 * EPollPoller构造函数
 */
EPollPoller::EPollPoller(EventLoop* loop)
    : Poller(loop),
      epollfd_(createEpollfd()),
      events_(kInitEventListSize) {
    LOG_TRACE << "EPollPoller created " << epollfd_;
}

/**
 * EPollPoller析构函数
 */
EPollPoller::~EPollPoller() {
    ::close(epollfd_);
}

/**
 * 等待事件发生
 */
Timestamp EPollPoller::poll(int timeoutMs, ChannelList* activeChannels) {
    LOG_TRACE << "fd total count " << channels_.size();

    int numEvents = ::epoll_wait(epollfd_, &*events_.begin(), 
                               static_cast<int>(events_.size()), timeoutMs);
    int savedErrno = errno;
    Timestamp now(Timestamp::now());

    if (numEvents > 0) {
        LOG_TRACE << numEvents << " events happened";
        fillActiveChannels(numEvents, activeChannels);
        if (implicit_cast<size_t>(numEvents) == events_.size()) {
            events_.resize(events_.size() * 2);
        }
    } else if (numEvents == 0) {
        LOG_TRACE << "nothing happened";
    } else {
        if (savedErrno != EINTR) {
            errno = savedErrno;
            LOG_ERROR << "EPollPoller::poll(): " << strerror(savedErrno);
        }
    }
    return now;
}

/**
 * 填写活跃的事件通道列表
 */
void EPollPoller::fillActiveChannels(int numEvents, ChannelList* activeChannels) const {
    assert(implicit_cast<size_t>(numEvents) <= events_.size());
    for (int i = 0; i < numEvents; ++i) {
        Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
        channel->set_revents(events_[i].events);
        activeChannels->push_back(channel);
    }
}

/**
 * 更新事件通道
 */
void EPollPoller::updateChannel(Channel* channel) {
    Poller::assertInLoopThread();
    const int index = channel->index();
    LOG_TRACE << "fd = " << channel->fd() 
              << " events = " << channel->events() 
              << " index = " << index;

    if (index == kNew || index == kDeleted) {
        // a new one, add with EPOLL_CTL_ADD
        int fd = channel->fd();
        if (index == kNew) {
            assert(channels_.find(fd) == channels_.end());
            channels_[fd] = channel;
        } else { // index == kDeleted
            assert(channels_.find(fd) != channels_.end());
            assert(channels_[fd] == channel);
        }

        channel->set_index(kAdded);
        update(EPOLL_CTL_ADD, channel);
    } else {
        // update existing one with EPOLL_CTL_MOD/DEL
        int fd = channel->fd();
        (void)fd;
        assert(channels_.find(fd) != channels_.end());
        assert(channels_[fd] == channel);
        assert(index == kAdded);
        if (channel->isNoneEvent()) {
            update(EPOLL_CTL_DEL, channel);
            channel->set_index(kDeleted);
        } else {
            update(EPOLL_CTL_MOD, channel);
        }
    }
}

/**
 * 移除事件通道
 */
void EPollPoller::removeChannel(Channel* channel) {
    Poller::assertInLoopThread();
    int fd = channel->fd();
    LOG_TRACE << "fd = " << fd;
    assert(channels_.find(fd) != channels_.end());
    assert(channels_[fd] == channel);
    assert(channel->isNoneEvent());
    int index = channel->index();
    assert(index == kAdded || index == kDeleted);
    size_t n = channels_.erase(fd);
    (void)n;
    assert(n == 1);

    if (index == kAdded) {
        update(EPOLL_CTL_DEL, channel);
    }
    channel->set_index(kNew);
}

/**
 * 执行epoll_ctl操作
 */
void EPollPoller::update(int operation, Channel* channel) {
    struct epoll_event event;
    memset(&event, 0, sizeof event);
    event.events = channel->events();
    event.data.ptr = channel;
    int fd = channel->fd();
    LOG_TRACE << "epoll_ctl op = " << operationToString(operation) 
              << ", fd = " << fd << ", event = { " << channel->events() 
              << " }, ptr = " << channel;
    
    if (::epoll_ctl(epollfd_, operation, fd, &event) < 0) {
        if (operation == EPOLL_CTL_DEL) {
            LOG_ERROR << "epoll_ctl op = " << operationToString(operation) 
                     << ", fd = " << fd << ": " << strerror(errno);
        } else {
            LOG_FATAL << "epoll_ctl op = " << operationToString(operation) 
                     << ", fd = " << fd << ": " << strerror(errno);
        }
    }
}