/*
C++11异步并发示例: async、future、packaged_task 和 promise

这个程序演示了C++11中四种异步并发机制的使用方法：
1. std::async 和 std::future：异步执行函数并获取结果
2. std::packaged_task：封装可调用对象为异步操作
3. std::promise：在一个线程中产生值，在另一个线程中获取值
*/
#include <iostream>
#include <future>
#include <thread>
#include <chrono>
using namespace std;

// 1. std::async 示例函数
int calculate_async()
{
    cout << "[Async] 开始耗时计算..." << endl;
    // 模拟一个耗时的计算
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 42;
}

// 2. packaged_task 示例函数
int calculate_sum(int x, int y)
{
    cout << "[Packaged Task] 计算 " << x << " + " << y << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 模拟计算时间
    return x + y;
}

// 3. promise 示例函数
void set_promise_value(std::promise<int> &p)
{
    cout << "[Promise] 准备设置值..." << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(800)); // 模拟准备时间
    p.set_value(1000);
    cout << "[Promise] 值已设置为 1000" << endl;
}

int main()
{
    cout << "=== C++11 异步并发示例 ===" << endl;
    
    // 示例1: 使用 std::async 和 std::future
    cout << "\n示例1: std::async 和 std::future" << endl;
    std::future<int> future_async = std::async(std::launch::async, calculate_async);
    cout << "主线程继续执行其他任务..." << endl;
    int result_async = future_async.get(); // 获取异步操作的结果
    cout << "异步计算结果: " << result_async << endl;
    
    // 示例2: 使用 std::packaged_task
    cout << "\n示例2: std::packaged_task" << endl;
    std::packaged_task<int(int, int)> task(calculate_sum);
    std::future<int> future_task = task.get_future();
    
    // 在新线程中执行任务
    std::thread t1(std::move(task), 10, 20);
    t1.join(); // 等待线程完成
    
    // 获取结果
    int result_task = future_task.get();
    cout << "Packaged task 结果: " << result_task << endl;
    
    // 示例3: 使用 std::promise
    cout << "\n示例3: std::promise" << endl;
    std::promise<int> promise_obj;
    std::future<int> future_promise = promise_obj.get_future();
    
    // 在新线程中设置promise的值
    std::thread t2(set_promise_value, std::ref(promise_obj));
    
    // 主线程等待并获取值
    cout << "主线程等待promise的值..." << endl;
    int result_promise = future_promise.get();
    cout << "从promise获取的值: " << result_promise << endl;
    
    t2.join(); // 等待线程完成
    
    cout << "\n=== 所有异步操作完成 ===" << endl;
    return 0;
}