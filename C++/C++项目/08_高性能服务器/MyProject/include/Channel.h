#ifndef MY_PROJECT_CHANNEL_H
#define MY_PROJECT_CHANNEL_H

#include <functional>
#include <memory>
#include "noncopyable.h"
#include "Timestamp.h"

class EventLoop;

/**
 * 事件通道类
 * 封装文件描述符和相关的事件
 * 管理事件的注册、修改和删除
 */
class Channel : noncopyable
{
public:
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void(Timestamp)>;

    Channel(EventLoop *loop, int fd);
    ~Channel();

    /**
     * 事件处理函数
     * @param receiveTime 事件发生的时间
     */
    void handleEvent(Timestamp receiveTime);

    /**
     * 设置回调函数
     */
    void setReadCallback(ReadEventCallback cb)
    {
        readCallback_ = std::move(cb);
    }
    void setWriteCallback(EventCallback cb)
    {
        writeCallback_ = std::move(cb);
    }
    void setCloseCallback(EventCallback cb)
    {
        closeCallback_ = std::move(cb);
    }
    void setErrorCallback(EventCallback cb)
    {
        errorCallback_ = std::move(cb);
    }

    /**
     * 设置事件的所属对象，用于延长对象生命周期
     */
    void tie(const std::shared_ptr<void> &obj);

    // 获取fd和事件信息
    int fd() const { return fd_; }
    int events() const { return events_; }
    void set_revents(int revt) { revents_ = revt; }
    bool isNoneEvent() const { return events_ == kNoneEvent; }

    /**
     * 事件操作
     */
    void enableReading()
    {
        events_ |= kReadEvent;
        update();
    }
    void disableReading()
    {
        events_ &= ~kReadEvent;
        update();
    }
    void enableWriting()
    {
        events_ |= kWriteEvent;
        update();
    }
    void disableWriting()
    {
        events_ &= ~kWriteEvent;
        update();
    }
    void disableAll()
    {
        events_ = kNoneEvent;
        update();
    }

    /**
     * 事件状态查询
     */
    bool isReading() const { return events_ & kReadEvent; }
    bool isWriting() const { return events_ & kWriteEvent; }

    /**
     * 用于poller的索引
     */
    int index() { return index_; }
    void set_index(int idx) { index_ = idx; }

    /**
     * 所属的EventLoop
     */
    EventLoop *ownerLoop() { return loop_; }
    void remove();

private:
    /**
     * 更新事件
     */
    void update();

    /**
     * 带保护的事件处理函数
     */
    void handleEventWithGuard(Timestamp receiveTime);

    /**
     * 事件类型常量
     */
    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop *loop_;
    const int fd_;
    int events_;  // 关注的事件
    int revents_; // 实际发生的事件
    int index_;   // 在Poller中的索引
    bool logHup_; // 记录POLLHUP事件

    std::weak_ptr<void> tie_; // 用于延长对象生命周期
    bool tied_;               // 是否已绑定对象
    bool eventHandling_;      // 是否正在处理事件
    bool addedToLoop_;        // 是否已添加到EventLoop

    // 回调函数
    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;
};

#endif // MY_PROJECT_CHANNEL_H