#include <iostream>
#include <thread>
#include <memory>
using namespace std;

// 1.传递临时变量的问题
/*
    问题：在创建线程时，传递了一个临时变量作为参数，而线程函数中引用了该参数。
    解决：使用ref()函数将参数转换为引用类型，确保线程函数中使用的是同一个变量。
*/
void foo1(int &x)
{
    x += 1;
}

// 2.传递指针或者引用指向局部变量的问题
/*
    问题：在创建线程时，传递了一个指针或者引用指向局部变量，而线程函数中使用了该指针或者引用。
    解决：确保线程函数中使用的指针或者引用指向的变量在线程函数执行期间是有效的。
*/
thread t2;
void foo2(int &x)
{
    x += 1;
}
int a2 = 1;
void test2()
{
    // int a2 = 1;
    t2 = thread(foo2, ref(a2));
    return;
}

// 3.传递指针或引用指向已释放的内存问题,和问题2一样，如果a在局部作用域，线程函数执行时a已经被释放，所以会导致未定义行为。
/*
    问题：在创建线程时，传递了一个指针或者引用指向已释放的内存，而线程函数中使用了该指针或者引用。
    解决：确保线程函数中使用的指针或者引用指向的变量在线程函数执行期间是有效的。
*/
void foo3(int *x)
{
    cout << *x << endl;
}
// 问题4.类成员函数作为入口函数，类对象被提前释放
/*
    问题：在创建线程时，传递了一个类成员函数作为入口函数，而类对象在创建线程之前就被提前释放了。
    解决：确保在创建线程之前，类对象的生命周期足够长，或者使用lambda表达式捕获类对象的引用。
*/
class MyClass
{
public:
    void foo4()
    {
        cout << "hello 问题4 智能指针" << endl;
    }
};
// 问题5:入口函数为类的私有成员函数
/*
    问题：在创建线程时，传递了一个类的私有成员函数作为入口函数，而线程函数中使用了该函数。
    解决：确保在创建线程之前，类的私有成员函数的访问权限足够高，或者使用lambda表达式捕获类的私有成员函数的引用。
*/
class MyClass1
{
private:
    friend void foo5(); // 声明foo5为友元函数，以便在foo5中调用类的私有成员函数foo4
    void foo5()
    {
        cout << "hello 问题5 使用友元让外部线程调用私有成员函数作为线程函数 " << endl;
    }
};

void foo5()
{
    shared_ptr<MyClass1> obj_ptr = make_shared<MyClass1>(); // 用shared_ptr管理类对象的生命周期
    thread t5(&MyClass1::foo5, obj_ptr);                   // 因为是指针，所以地址一直有效
    t5.join();
}

int main()
{
    // 问题1
    int a1 = 1;
    thread t1(foo1, ref(a1));
    t1.join();
    cout << a1 << endl;

    // 问题2
    test2();
    t2.join();
    cout << a2 << endl;

    // 问题3
    int *ptr = new int(1); // 申请内存，数值为1
    thread t3(foo3, ptr);  // 将ptr传递后，立马释放ptr，导致线程函数中使用了已释放的内存
    delete ptr;
    t3.join(); // 等待线程执行完毕

    // 问题4
    // 智能指针的好处：智能指针的类不再需要的时候，就会调用智能指针的析构函数，自动释放类对象的内存
    shared_ptr<MyClass> obj_ptr = make_shared<MyClass>(); // 用shared_ptr管理类对象的生命周期
    thread t4(&MyClass::foo4, obj_ptr);                   // 因为是指针，所以地址一直有效
    t4.join();

    // 问题5
    foo5();
    return 0;
}