/*
std::condition_variable 的步骤如下：
1.创建一个 std::condition_variable 对象。
2.创建一个互斥锁 std::mutex 对象，用来保护共享资源的访问。
3.在需要等待条件变量的地方使用 std::unique_lock 对象锁定互斥锁并调用 std::condition_variable::wait()、std::condition_variable::wait_for() 或 std::condition_variable::wait_until() 函数等待条件变量。
4.在其他线程中需要通知等待的线程时，调用 std::condition_variable::notify_one() 或 std::condition_variable::notify_all() 函数通知等待的线程。
生产者与消费者模型
下面是一个简单的生产者-消费者模型的案例，其中使用了 std::condition_variable 来实现线程的等待和通知机制：
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>
std::mutex g_mutex;
std::condition_variable g_cv;
std::queue<int> g_queue;
std::atomic<bool> g_is_producer_done(false); // 标记生产者是否已完成
// 生产者线程函数，不断生产数据并放入队列中
void Producer()
{
    for (int i = 0; i < 10; i += 1)
    {
        {
            std::unique_lock<std::mutex> lock(g_mutex);
            g_queue.push(i);
            std::cout << "Producer: produced " << i << std::endl;
        }
        g_cv.notify_one(); // 调用notify_one()函数通知提醒等待的线程，告诉他们队列里有数据了，阻塞状态可以解除
        // g_cv.notify_all();//调用notify_all()函数通知提醒所有等待的线程，告诉他们队列里有数据了，阻塞状态可以解除
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    // 生产者完成后设置标记并通知消费者
    g_is_producer_done = true;
    g_cv.notify_one(); // 通知最后可能在等待的消费者线程
}
// 消费者线程函数，不断从队列中取出数据并消费
void Consumer()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(g_mutex);
        // lambda表达式，判断队列是否为空，如果不为空或生产者已完成，就继续执行
        g_cv.wait(lock, []()
                  { return !g_queue.empty() || g_is_producer_done; });
        
        // 如果队列不为空，消费数据
        if (!g_queue.empty()) {
            int value = g_queue.front();
            g_queue.pop();
            std::cout << "Consumer: consumed " << value << std::endl;
        } else if (g_is_producer_done) {
            // 如果队列为空且生产者已完成，则退出循环
            std::cout << "Consumer: producer done, exiting..." << std::endl;
            break;
        }
    }
}
int main()
{
    std::thread producer_thread(Producer);
    std::thread consumer_thread(Consumer);
    producer_thread.join();
    consumer_thread.join();
    return 0;
}