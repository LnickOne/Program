#include <iostream>
#include <thread>
#include <string>
using namespace std;

void printHello(string name)
{
    for (int i = 0; i <= 50; i += 1)
    {
        cout << i << " ";
    }
    cout << endl;
    cout << "hello " << endl;
    cout << "hello " << name << endl;
}
int main()
{
    // 1、创建线程
    // 需要一个可调用函数或者可调用对象，作为线程的入口点，在C++中，可调用函数包括普通函数、函数指针、lambda表达式、bind表达式等。
    // 语法：thread thread1(可调用函数或可调用对象, 可调用函数的参数);
    // 进程就是运行中的程序，线程就是进程中的进程，每个进程至少有一个线程，即主线程。一个线程即是一个执行流，每个线程都有自己的栈空间、程序计数器、寄存器等。
    thread thread1(printHello, "thread");
    // thread1.join();,如果不加join,主程序就会直接执行return 0,而不会等待thread1执行完毕
    // thread1.detach(); 分离线程，主线程和子线程独立执行，主线程不会等待子线程执行完毕。使用不多，因为主线程无法知道子线程是否执行完毕。
    bool isJoin = thread1.joinable();
    if (isJoin)
    {
        cout << "thread1 is joinable" << endl;
        thread1.join(); // join是阻塞主线程，直到子线程执行完毕
    }
    cout << "over" << endl;
    return 0;
}