#include <iostream>
#include <mutex>
using namespace std;

// 1. 基本饱汉式单例（非线程安全）
class SingletonLazyBasic
{
private:
    SingletonLazyBasic()
    {
        cout << "基本饱汉式单例构造函数调用" << endl;
    }

    SingletonLazyBasic(const SingletonLazyBasic &) = delete;
    SingletonLazyBasic &operator=(const SingletonLazyBasic &) = delete;

    // 静态指针，初始化为nullptr
    static SingletonLazyBasic *instance;

public:
    static SingletonLazyBasic *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new SingletonLazyBasic();
        }
        return instance;
    }

    void showMessage()
    {
        cout << "Hello from SingletonLazyBasic!" << endl;
    }
};

// 类外初始化静态指针
SingletonLazyBasic *SingletonLazyBasic::instance = nullptr;

// 2. 线程安全的饱汉式单例（双重检查锁定）
class SingletonLazyThreadSafe
{
private:
    SingletonLazyThreadSafe()
    {
        cout << "线程安全饱汉式单例构造函数调用" << endl;
    }

    SingletonLazyThreadSafe(const SingletonLazyThreadSafe &) = delete;
    SingletonLazyThreadSafe &operator=(const SingletonLazyThreadSafe &) = delete;

    // 静态指针，初始化为nullptr
    static SingletonLazyThreadSafe *instance;
    // 互斥锁用于线程同步
    static mutex mtx;

public:
    static SingletonLazyThreadSafe *getInstance()
    {
        // 第一次检查，避免每次都加锁
        if (instance == nullptr)
        {
            // 加锁保护
            mtx.lock();
            // 第二次检查，确保只创建一个实例
            if (instance == nullptr)
            {
                instance = new SingletonLazyThreadSafe();
            }
            mtx.unlock();
        }
        return instance;
    }

    void showMessage()
    {
        cout << "Hello from SingletonLazyThreadSafe!" << endl;
    }
};

// 类外初始化静态成员
SingletonLazyThreadSafe *SingletonLazyThreadSafe::instance = nullptr;
mutex SingletonLazyThreadSafe::mtx;

// 3. C++11线程安全的饱汉式单例（局部静态变量）
class SingletonLazyC11
{
private:
    SingletonLazyC11()
    {
        cout << "C++11饱汉式单例构造函数调用" << endl;
    }

    SingletonLazyC11(const SingletonLazyC11 &) = delete;
    SingletonLazyC11 &operator=(const SingletonLazyC11 &) = delete;

public:
    // C++11标准保证局部静态变量的初始化是线程安全的
    static SingletonLazyC11 &getInstance()
    {
        static SingletonLazyC11 instance;
        return instance;
    }

    void showMessage()
    {
        cout << "Hello from SingletonLazyC11!" << endl;
    }
};

int main()
{
    cout << "程序启动" << endl;
    cout << "\n--- 基本饱汉式单例测试 ---" << endl;
    SingletonLazyBasic *s1 = SingletonLazyBasic::getInstance();
    SingletonLazyBasic *s2 = SingletonLazyBasic::getInstance();
    cout << "s1地址: " << s1 << endl;
    cout << "s2地址: " << s2 << endl;
    s1->showMessage();

    cout << "\n--- 线程安全饱汉式单例测试 ---" << endl;
    SingletonLazyThreadSafe *s3 = SingletonLazyThreadSafe::getInstance();
    SingletonLazyThreadSafe *s4 = SingletonLazyThreadSafe::getInstance();
    cout << "s3地址: " << s3 << endl;
    cout << "s4地址: " << s4 << endl;
    s3->showMessage();

    cout << "\n--- C++11饱汉式单例测试 ---" << endl;
    SingletonLazyC11 &s5 = SingletonLazyC11::getInstance();
    SingletonLazyC11 &s6 = SingletonLazyC11::getInstance();
    cout << "s5地址: " << &s5 << endl;
    cout << "s6地址: " << &s6 << endl;
    s5.showMessage();

    return 0;
}