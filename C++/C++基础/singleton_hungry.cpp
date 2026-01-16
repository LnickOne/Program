#include <iostream>
using namespace std;

// 饿汉式单例模式
class SingletonHungry
{
private:
    // 1. 构造函数私有化
    SingletonHungry()
    {
        cout << "饿汉式单例构造函数调用" << endl;
    }

    // 2. 拷贝构造函数和赋值运算符私有化，防止拷贝
    SingletonHungry(const SingletonHungry &) = delete;
    SingletonHungry &operator=(const SingletonHungry &) = delete;

    // 3. 静态成员变量，在类外初始化，程序启动时就创建实例
    static SingletonHungry instance;

public:
    // 4. 静态成员函数，提供全局访问点
    static SingletonHungry &getInstance()
    {
        return instance;
    }

    void showMessage()
    {
        cout << "Hello from SingletonHungry!" << endl;
    }
};

// 类外初始化静态成员变量
SingletonHungry SingletonHungry::instance;

int main()
{
    cout << "程序启动" << endl;

    // 获取单例实例
    SingletonHungry &s1 = SingletonHungry::getInstance();
    SingletonHungry &s2 = SingletonHungry::getInstance();

    // 验证是否是同一个实例
    cout << "s1地址: " << &s1 << endl;
    cout << "s2地址: " << &s2 << endl;

    s1.showMessage();

    return 0;
}