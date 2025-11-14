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