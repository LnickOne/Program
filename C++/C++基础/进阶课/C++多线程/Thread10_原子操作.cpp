/*
std::atomic 是 C++11 标准库中的一个模板类，用于实现多线程环境下的原子操作。
它提供了一种线程安全的方式来访问和修改共享变量，可以避免多线程环境中的数据竞争问题。
std::atomic 的使用方式类似于普通的 C++ 变量，但是它的操作是原子性的。
也就是说，在多线程环境下，多个线程同时对同一个 std::atomic 变量进行操作时，不会出现数据竞争问题。
以下是一些常用的 std::atomic 操作：
1. load()：将 std::atomic 变量的值加载到当前线程的本地缓存中，并返回这个值。
2. store(val)：将 val 的值存储到 std::atomic 变量中，并保证这个操作是原子性的。
3. exchange(val)：将 val 的值存储到 std::atomic 变量中，并返回原先的值。
4. compare_exchange_weak(expected, val) 和 compare_exchange_strong(expected, val)：比较 std::atomic 变量的值和 expected 的值是否相同，如果相同，则将 val 的值存储到 std::atomic 变量中，并返回 true；否则，将 std::atomic 变量的值存储到 expected 中，并返回 false。
以下是一个示例，演示了如何使用 std::atomic 进行原子操作：
*/
#include <atomic>
#include <iostream>
#include <thread>
std::atomic<int> count(0);
void increment()
{
    for (int i = 0; i < 1000000; i += 1)
    {
        count += 1;
    }
}
int main()
{
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    std::cout << count << std::endl;
    return 0;
}
/*
在这个示例中，我们定义了一个 std::atomic<int> 类型的变量 count，并将其初始化为 0。
然后，我们启动两个线程分别执行 increment 函数，这个函数的作用是将 count 变量的值加一，执行一百万次。
最后，我们在主线程中输出 count 变量的值。
由于 count 变量是一个 std::atomic 类型的变量，因此对它进行操作是原子性的，不会出现数据竞争问题。
在这个示例中，最终输出的 count 变量的值应该是 2000000
原子性数据效率更高。
*/