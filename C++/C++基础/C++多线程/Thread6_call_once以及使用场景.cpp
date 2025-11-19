/*
单例设计模式是一种常见的设计模式，用于确保某个类只能创建一个实例。
由于单例实例是全局唯一的，因此在多线程环境中使用单例模式时，需要考虑线程安全的问题。
全局只需要创建一个对象，不需要更多的对象，比如日志类LOG，提示信息，报错信息，都通过这个类打印到日志文件或者屏幕
*/
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
// class Log
// {
// public:
//     Log() {}
//     // 因为是单例模式，不需要多个对象，所以禁用拷贝构造和赋值运算符
//     Log(const Log &log) = delete;
//     Log &operator=(const Log &log) = delete;
//     // 全局只需要一个对象，用静态成员函数来获取实例
//     static Log &getInstance()
//     {
//         static Log log; // 懒汉模式，提前创建了对象，来了就给
//         // static Log *log = nullptr; // 饿汉模式，提前不声明对象，先创建空指针，如果来了之后是nullptr，就创建一个对象，否则就返回已经创建的对象
//         // if (log == nullptr)
//         // {
//         //     log = new Log;
//         // }
//         // return *log;
//         return log;
//     }
//     void printLog(const string &msg)
//     {
//         cout << __TIME__ << " " << msg << endl;
//     }
// };
// void print_error()
// {
//     Log::getInstance().printLog("这里有错误");
// }
// int main()
// {
//     thread t1(print_error);
//     thread t2(print_error);
//     t1.join();
//     t2.join();
//     return 0;
// }
/*在这个单例类中，我们使用了一个静态成员函数 getInstance() 来获取单例实例，该函数使用了一个静态局部变量 instance 来存储单例实例。
由于静态局部变量只会被初始化一次，因此该实现可以确保单例实例只会被创建一次。但是，该实现并不是线程安全的。
如果多个线程同时调用 getInstance() 函数，可能会导致多个对象被创建，从而违反了单例模式的要求。
此外，如果多个线程同时调用 setData() 函数来修改单例对象的数据成员 data，可能会导致数据不一致或不正确的结果。
为了解决这些问题，我们可以使用 std::call_once 来实现一次性初始化，从而确保单例实例只会被创建一次。
下面是一个使用 std::call_once 的单例实现：
*/
class Log
{
private:
    // 私有构造函数
    Log() {}
    // 因为是单例模式，不需要多个对象，所以禁用拷贝构造和赋值运算符
    Log(const Log &log) = delete;
    Log &operator=(const Log &log) = delete;

    // 静态成员指针，存储单例实例
    static Log *log;

    // 确保程序结束时释放单例对象
    class Deleter
    {
    public:
        ~Deleter()
        {
            if (Log::log != nullptr)
            {
                delete Log::log;
                Log::log = nullptr;
            }
        }
    };
    static Deleter deleter; // 用于自动释放内存的静态成员

public:
    // 全局只需要一个对象，用静态成员函数来获取实例
    static Log &getInstance()
    {
        // 使用call_once确保init只被调用一次，保证线程安全
        static std::once_flag once;
        std::call_once(once, init); // call_once确保init()函数只被调用一次，保证线程安全
        return *log;
    };

    static void init()
    {
        // 只在init函数中创建实例，确保线程安全
        if (log == nullptr)
        {
            log = new Log;
        }
    }

    void printLog(const string &msg)
    {
        cout << __TIME__ << " " << msg << endl;
    }
};

// 定义静态成员变量
Log *Log::log = nullptr;
Log::Deleter Log::deleter;
void print_error()
{
    Log::getInstance().printLog("这里有错误");
}
int main()
{
    thread t1(print_error);
    thread t2(print_error);
    t1.join();
    t2.join();
    return 0;
}
// class Singleton
// {
// public:
//     static Singleton &getInstance()
//     {
//         std::call_once(m_onceFlag, &Singleton::init);
//         return *m_instance;
//     }
//     void setData(int data)
//     {
//         m_data = data;
//     }
//     int getData() const
//     {
//         return m_data;
//     }

// private:
//     Singleton() {}
//     Singleton(const Singleton &) = delete;
//     Singleton &operator=(const Singleton &) = delete;
//     static void init()
//     {
//         m_instance.reset(new Singleton);
//     }
//     static std::unique_ptr<Singleton> m_instance;
//     static std::once_flag m_onceFlag;
//     int m_data = 0;
// };
// std::unique_ptr<Singleton> Singleton::m_instance;
// std::once_flag Singleton::m_onceFlag;

/*
在这个实现中，我们使用了一个静态成员变量 m_instance 来存储单例实例，使用了一个静态成员变量 m_onceFlag 来标记初始化是否已经完成。在 getInstance() 函数中，我们使用 std::call_once 来调用 init() 函数，确保单例实例只会被创建一次。在 init() 函数中，我们使用了 std::unique_ptr 来创建单例实例。

使用 std::call_once 可以确保单例实例只会被创建一次，从而避免了多个对象被创建的问题。此外，使用 std::unique_ptr 可以确保单例实例被正确地释放，避免了内存泄漏的问题。

std::call_once 是 C++11 标准库中的一个函数，用于确保某个函数只会被调用一次。其函数原型如下：

template<class Callable, class... Args>

void call_once(std::once_flag& flag, Callable&& print_error, Args&&... args);

其中，flag 是一个 std::once_flag 类型的对象，用于标记函数是否已经被调用；print_error 是需要被调用的函数或可调用对象；args 是函数或可调用对象的参数。

std::call_once 的作用是，确保在多个线程中同时调用 call_once 时，只有一个线程能够成功执行 print_error 函数，而其他线程则会等待该函数执行完成。

使用 std::call_once 的过程中，需要注意以下几点：

\1. flag 参数必须是一个 std::once_flag 类型的对象，并且在多次调用 call_once 函数时需要使用同一个 flag 对象。

\2. print_error 参数是需要被调用的函数或可调用对象。该函数只会被调用一次，因此应该确保该函数是幂等的。

\3. args 参数是 print_error 函数或可调用对象的参数。如果 print_error 函数没有参数，则该参数可以省略。

\4. std::call_once 函数会抛出 std::system_error 异常，如果在调用 print_error 函数时发生了异常，则该异常会被传递给调用者。

使用 std::call_once 可以在多线程环境中实现一次性初始化，避免了多个线程同时初始化的问题。例如，在单例模式中，可以使用 std::call_once 来保证单例实例只会被创建一次。
*/