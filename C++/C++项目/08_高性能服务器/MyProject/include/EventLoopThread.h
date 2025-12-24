#ifndef EVENT_LOOP_THREAD_H
#define EVENT_LOOP_THREAD_H

#include "noncopyable.h"
#include <string>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

class EventLoop;

/**
 * EventLoopThread类
 * 负责创建一个新线程，并在该线程中创建EventLoop对象
 */
class EventLoopThread : noncopyable
{
public:
    using ThreadInitCallback = std::function<void(EventLoop *)>;

    /**
     * 构造函数
     * @param cb 线程初始化回调函数
     * @param name 线程名称
     */
    EventLoopThread(const ThreadInitCallback &cb = ThreadInitCallback(),
                    const std::string &name = std::string());

    /**
     * 析构函数
     */
    ~EventLoopThread();

    /**
     * 启动线程
     * @return EventLoop对象指针
     */
    EventLoop *startLoop();

    /**
     * 获取线程ID
     * @return 线程ID
     */
    std::thread::id tid() const
    {
        if (thread_)
        {
            return thread_->get_id();
        }
        return std::thread::id(); // 返回默认的线程ID
    }

    /**
     * 获取线程名称
     * @return 线程名称
     */
    const std::string &name() const { return name_; }

private:
    /**
     * 线程运行函数
     */
    void threadFunc();

    ThreadInitCallback callback_;         // 线程初始化回调
    std::string name_;                    // 线程名称
    std::unique_ptr<std::thread> thread_; // 线程对象
    std::mutex mutex_;                    // 互斥锁
    std::condition_variable cond_;        // 条件变量
    EventLoop *loop_;                     // EventLoop对象指针
    bool exiting_;                        // 是否退出
};

#endif // EVENT_LOOP_THREAD_H