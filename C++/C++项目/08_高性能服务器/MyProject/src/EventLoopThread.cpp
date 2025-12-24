#include "EventLoopThread.h"
#include "EventLoop.h"
#include "Logger.h"

#include <functional>
#include <assert.h>

EventLoopThread::EventLoopThread(const ThreadInitCallback &cb, const std::string &name)
    : callback_(cb),
      name_(name),
      loop_(nullptr),
      exiting_(false)
{
    LOG_INFO << "EventLoopThread constructor";
}

EventLoopThread::~EventLoopThread()
{
    exiting_ = true;
    if (loop_ != nullptr)
    {
        loop_->quit();
        thread_->join();
    }
    LOG_INFO << "EventLoopThread destructor";
}

EventLoop *EventLoopThread::startLoop()
{
    assert(thread_ == nullptr);
    // 创建线程
    thread_.reset(new std::thread(std::bind(&EventLoopThread::threadFunc, this)));

    EventLoop *loop = nullptr;
    {
        std::unique_lock<std::mutex> lock(mutex_);
        // 等待线程初始化完成
        while (loop_ == nullptr)
        {
            cond_.wait(lock);
        }
        loop = loop_;
    }

    return loop;
}

void EventLoopThread::threadFunc()
{
    EventLoop loop;

    if (callback_)
    {
        callback_(&loop);
    }

    {
        std::unique_lock<std::mutex> lock(mutex_);
        loop_ = &loop;
        cond_.notify_one();
    }

    loop.loop();

    std::unique_lock<std::mutex> lock(mutex_);
    loop_ = nullptr;
}