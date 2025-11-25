/*
使用 C++11 标准库中的 std::thread、std::mutex、std::condition_variable、std::function 和 std::queue 等组件实现。
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>
class ThreadPool
{
private:
    std::vector<std::thread> threads;        // 线程池中的线程数组
    std::queue<std::function<void()>> tasks; // 任务队列
    std::mutex mutex;                        // 互斥锁，用于保护任务队列的访问
    std::condition_variable condition;       // 条件变量，用于线程间通信
    bool stop;                               // 标志位，用于指示线程池是否停止运行
public:
    ThreadPool(int numThreads) : stop(false) // 构造函数，初始化线程池需要开辟多少个线程
    {
        for (int i = 0; i < numThreads; ++i)
        { // 因为push_back会进行拷贝构造，而emplace_back会直接调用成员函数的构造函数，移动构造，所以这里用emplace_back节省资源
            threads.emplace_back([this]
                                 {
            while (true) {
                std::unique_lock<std::mutex> lock(mutex);
                condition.wait(lock, [this] { return stop || !tasks.empty(); });
                if (stop && tasks.empty()) {
                    return;// 如果线程池停止运行且任务队列为空，退出循环
                }
                std::function<void()> task(std::move(tasks.front()));// 从任务队列中取出一个任务，移动构造到task中
                tasks.pop();
                lock.unlock();
                task();// 执行任务
            } });
        }
    }

    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread &thread : threads)
        {
            thread.join();
        }
    }

    template <typename F, typename... Args>
    void enqueue(F &&f, Args &&...args)
    {
        std::function<void()> task(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        {
            std::unique_lock<std::mutex> lock(mutex);
            tasks.emplace(std::move(task));
        }
        condition.notify_one();
    }
};

int main()
{
    ThreadPool pool(4); // 创建一个线程池，包含 4 个线程
    for (int i = 0; i < 10; ++i)
    { // 向线程池提交 10 个任务
        pool.enqueue([i]
                     {
            std::cout << "Task " << i << " is running in thread " << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "Task " << i << " is done" << std::endl; });
    }
    return 0;
}