#ifndef EVENT_LOOP_THREAD_POOL_H
#define EVENT_LOOP_THREAD_POOL_H

#include "noncopyable.h"
#include <vector>
#include <string>
#include <functional>
#include <memory>

class EventLoop;
class EventLoopThread;

/**
 * EventLoopThreadPool类
 * 管理多个EventLoopThread对象，为TcpServer提供线程池支持
 */
class EventLoopThreadPool : noncopyable
{
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>;

    /**
     * 构造函数
     * @param baseLoop 基础EventLoop对象
     * @param name 线程池名称
     */
    EventLoopThreadPool(EventLoop* baseLoop, const std::string& name);

    /**
     * 析构函数
     */
    ~EventLoopThreadPool();

    /**
     * 设置线程数量
     * @param numThreads 线程数量
     */
    void setThreadNum(int numThreads) { numThreads_ = numThreads; }

    /**
     * 启动线程池
     */
    void start(const ThreadInitCallback& cb = ThreadInitCallback());

    /**
     * 获取下一个EventLoop对象
     * @return EventLoop对象指针
     */
    EventLoop* getNextLoop();

    /**
     * 获取所有EventLoop对象
     * @return EventLoop对象指针列表
     */
    std::vector<EventLoop*> getAllLoops();

    /**
     * 检查线程池是否已经启动
     * @return 是否已经启动
     */
    bool started() const { return started_; }

    /**
     * 获取线程池名称
     * @return 线程池名称
     */
    const std::string& name() const { return name_; }

private:
    EventLoop* baseLoop_;           // 基础EventLoop对象
    std::string name_;              // 线程池名称
    bool started_;                  // 是否已经启动
    int numThreads_;                // 线程数量
    int next_;                      // 下一个要使用的线程索引
    std::vector<std::unique_ptr<EventLoopThread>> threads_;  // EventLoopThread对象列表
    std::vector<EventLoop*> loops_; // EventLoop对象列表
};

#endif // EVENT_LOOP_THREAD_POOL_H