/*
unique_lock：
-unique_lock 是 C++ 标准库中提供的一个互斥量封装类，用于在多线程程序中对互斥量进行加锁和解锁操作。
-主要特点是可以对互斥量进行更加灵活的管理，包括延迟加锁、条件变量、超时等。

unique_lock 提供了以下几个成员函数：
-lock()：尝试对互斥量进行加锁操作，如果当前互斥量已经被其他线程持有，则当前线程会被阻塞，直到互斥量被成功加锁。
-try_lock()：尝试对互斥量进行加锁操作，如果当前互斥量已经被其他线程持有，则函数立即返回 false，否则返回 true。
-try_lock_for(const chrono::duration<Rep, Period>& rel_time)：尝试对互斥量进行加锁操作，如果当前互斥量已经被其他线程持有，则当前线程会被阻塞，直到互斥量被成功加锁，或者超过了指定的时间。
-try_lock_until(const chrono::time_point<Clock, Duration>& abs_time)：尝试对互斥量进行加锁操作，如果当前互斥量已经被其他线程持有，则当前线程会被阻塞，直到互斥量被成功加锁，或者超过了指定的时间点。
-unlock()：对互斥量进行解锁操作。

除了上述成员函数外，unique_lock 还提供了以下几个构造函数：
-unique_lock() noexcept = default：默认构造函数，创建一个未关联任何互斥量的 unique_lock 对象。
-explicit unique_lock(mutex_type& m)：构造函数，使用给定的互斥量 m 进行初始化，并对该互斥量进行加锁操作。
-unique_lock(mutex_type& m, defer_lock_t) noexcept：构造函数，使用给定的互斥量 m 进行初始化，但不对该互斥量进行加锁操作。
-unique_lock(mutex_type& m, try_to_lock_t) noexcept：构造函数，使用给定的互斥量 m 进行初始化，并尝试对该互斥量进行加锁操作。如果加锁失败，则创建的 unique_lock 对象不与任何互斥量关联。
-unique_lock(mutex_type& m, adopt_lock_t) noexcept：构造函数，使用给定的互斥量 m 进行初始化，并假设该互斥量已经被当前线程成功加锁。
-unique_lock(unique_lock&& u) noexcept：移动构造函数，将另一个 unique_lock 对象 u 移动到当前对象中。
-unique_lock& operator=(unique_lock&& u) noexcept：移动赋值运算符，将另一个 unique_lock 对象 u 移动到当前对象中。
*/
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
int share_a = 0;
mutex mtx;
timed_mutex timed_mtx;
void func()
{
    /*
    lock_guard：
    lock_guard 是 C++ 标准库中的一种互斥量封装类，用于保护共享数据，防止多个线程同时访问同一资源而导致的数据竞争问题。
    lock_guard 的特点如下：
    -当构造函数被调用时，该互斥量会被自动锁定。
    -当析构函数被调用时，该互斥量会被自动解锁。
    -lock_guard 对象不能复制或移动，因此它只能在局部作用域中使用。
    */
    for (int i = 0; i < 2; i += 1)
    {
        // lock_guard<mutex> lock(mtx);            // 使用lock_guard,访问share_a并且想写操作的时候加锁，调用lock_guard的构造函数，自动对互斥量mtx加锁，在lock_guard对象的生命周期结束时，自动对互斥量mtx解锁，也就不需要mtx.lock()和mtx.unlock()了
        // unique_lock<mutex> lock(mtx);           // 使用unique_lock,访问share_a并且想写操作的时候加锁调用unique_lock的构造函数，自动对互斥量mtx加锁，在unique_lock对象的生命周期结束时，自动对互斥量mtx解锁，也就不需要mtx.lock()和mtx.unlock()了
        unique_lock<timed_mutex> lock(timed_mtx, defer_lock); // 传入defer_lock标签，说明构造函数不会对互斥量mtx加锁，需要在后续代码中手动调用lock()函数加锁
        if (lock.try_lock_for(chrono::seconds(2)))            // 尝试对互斥量mtx加锁，最多等待5秒，如果5秒内加锁成功，则返回true，否则返回false
        {
            this_thread::sleep_for(chrono::seconds(1)); // 模拟其他操作，确保在加锁前其他线程有机会对mtx加锁
            share_a += 1;
        }
    }
}

int main()
{
    thread t1(func);
    thread t2(func);
    t1.join();
    t2.join();
    cout << share_a << endl;
    return 0;
}