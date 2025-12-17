#include "Channel.h"
#include "EventLoop.h"
#include "Logger.h"

#include <cassert>
#include <sstream>
#include <poll.h>

/**
 * 事件类型常量定义
 */
const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

/**
 * 构造函数
 */
Channel::Channel(EventLoop *loop, int fd)
    : loop_(loop),
      fd_(fd),
      events_(0),
      revents_(0),
      index_(-1),
      logHup_(true),
      tied_(false),
      eventHandling_(false),
      addedToLoop_(false)
{
}

/**
 * 析构函数
 */
Channel::~Channel()
{
    assert(!eventHandling_);
    assert(!addedToLoop_);
    if (loop_->isInLoopThread())
    {
        assert(!loop_->hasChannel(this));
    }
}

/**
 * 设置事件的所属对象
 */
void Channel::tie(const std::shared_ptr<void> &obj)
{
    tie_ = obj;
    tied_ = true;
}

/**
 * 更新事件
 */
void Channel::update()
{
    addedToLoop_ = true;
    loop_->updateChannel(this);
}

/**
 * 移除事件
 */
void Channel::remove()
{
    assert(isNoneEvent());
    addedToLoop_ = false;
    loop_->removeChannel(this);
}

/**
 * 事件处理函数
 */
void Channel::handleEvent(Timestamp receiveTime)
{
    std::shared_ptr<void> guard;
    if (tied_)
    {
        guard = tie_.lock();
        if (guard)
        {
            handleEventWithGuard(receiveTime);
        }
    }
    else
    {
        handleEventWithGuard(receiveTime);
    }
}

/**
 * 带保护的事件处理函数
 */
void Channel::handleEventWithGuard(Timestamp receiveTime)
{
    eventHandling_ = true;
    LOG_TRACE << "文件描述符 = " << fd_ << " 关注事件 = " << events_ << " 实际事件 = " << revents_;

    if ((revents_ & POLLHUP) && !(revents_ & POLLIN))
    {
        if (logHup_)
        {
            LOG_WARN << "文件描述符 = " << fd_ << " Channel::handle_event()：POLLHUP事件";
        }
        if (closeCallback_)
            closeCallback_();
    }

    if (revents_ & POLLNVAL)
    {
        LOG_WARN << "文件描述符 = " << fd_ << " Channel::handle_event()：POLLNVAL事件";
    }

    if (revents_ & (POLLERR | POLLNVAL))
    {
        if (errorCallback_)
            errorCallback_();
    }

    if (revents_ & (POLLIN | POLLPRI | POLLRDHUP))
    {
        if (readCallback_)
            readCallback_(receiveTime);
    }

    if (revents_ & POLLOUT)
    {
        if (writeCallback_)
            writeCallback_();
    }

    eventHandling_ = false;
}