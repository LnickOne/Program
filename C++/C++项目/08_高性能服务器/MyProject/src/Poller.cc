// Copyright 2024. All Rights Reserved.
// Author: xxx@xxx.com

#include "Poller.h"
#include "Channel.h"
#include "EventLoop.h"
#include "Logger.h"

#include <assert.h>

/**
 * Poller构造函数
 */
Poller::Poller(EventLoop* loop) : ownerLoop_(loop) {
}

/**
 * Poller析构函数
 */
Poller::~Poller() = default;

/**
 * 检查事件通道是否在Poller中
 */
bool Poller::hasChannel(Channel* channel) const {
    assertInLoopThread();
    ChannelMap::const_iterator it = channels_.find(channel->fd());
    return it != channels_.end() && it->second == channel;
}

/**
 * 断言是否在EventLoop线程中
 */
void Poller::assertInLoopThread() const {
    ownerLoop_->assertInLoopThread();
}