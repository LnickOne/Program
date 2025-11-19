#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
/*
问题：死锁问题
假设有两个线程T1和T2，它们需要对两个互斥量mtx1和mtx2进行访问，而且需要按照以下顺序获取互斥量的所有权
- T1先获取mtx1的所有权，再获取mtx2的所有权
- T2先获取mtx2的所有权，再获取mtx1的所有权
如果两个线程同时进行，就会出现死锁问题。因为T1先获取mtx1的所有权，但是无法获取mtx2的所有权，而T2先获取mtx2的所有权，但是无法获取mtx1的所有权。
两个线程都在等待对方释放互斥量，但是都无法释放，所以就会出现死锁问题。

解决：
- 避免循环等待：确保每个线程获取互斥量的顺序是一致的，避免出现循环等待的情况。
- 及时释放互斥量：确保每个线程在使用完互斥量后及时释放，避免出现死锁问题。
*/
mutex mtx1, mtx2;
void func_1()
{
    for (int i = 0; i < 50000; i += 1)
    {
        // T1依次对mtx1和mtx2进行加锁，获取所有权
        mtx1.lock();
        mtx2.lock();
        // 对mtx1和mtx2依次解锁
        mtx1.unlock();
        mtx2.unlock();
    }
}
void func_2()
{
    // 问题：如果T2先获取mtx2的所有权，再获取mtx1的所有权，就会出现死锁问题。
    // for (int i = 0; i < 50000; i += 1)
    // {
    //     // T2先获取mtx2的所有权，再获取mtx1的所有权
    //     mtx2.lock();
    //     mtx1.lock();
    //     // 对mtx1和mtx2进行操作
    //     mtx1.unlock();
    //     mtx2.unlock();
    // }

    // 解决：将获取互斥量的顺序改为先获取mtx1的所有权，再获取mtx2的所有权，就可以避免死锁问题。
    for (int i = 0; i < 50000; i += 1)
    {
        // T2先获取mtx2的所有权，再获取mtx1的所有权
        mtx1.lock();
        mtx2.lock();
        // 对mtx1和mtx2进行操作
        mtx1.unlock();
        mtx2.unlock();
    }
}

int main()
{
    thread t1(func_1);
    thread t2(func_2);
    t1.join();
    t2.join();
    cout << "over" << endl;
    return 0;
}