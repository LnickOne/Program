#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
/*
在多个线程中共享数据时，需要使用互斥量来保护数据，避免多个线程同时访问数据导致数据不一致的问题。
*/
// 如果多线程程序每一次的运行结果和单线程运行的结果始终是一样的，那么这个多线程程序就是线程安全的
int a = 0;
mutex mtx;
void func()
{
    for (int i = 0; i < 100000; i += 1)
    {
        // 访问a并且想写操作的时候加锁
        mtx.lock();
        a += 1;
        // 操作结束解锁，表示写的过程只有单独一个线程可以访问，线程安全的典型案例
        mtx.unlock();
    }
}

int main()
{
    // 问题：两个线程同时访问a，导致a的值不是200000
    // 解决：使用互斥量(也可以叫互斥锁)mutex保护a，确保每次只有一个线程访问a，即T1访问a时，T2阻塞等待，T2访问a时，T1阻塞等待
    thread t1(func);
    thread t2(func);
    t1.join();
    t2.join();
    cout << a << endl;
    return 0;
}