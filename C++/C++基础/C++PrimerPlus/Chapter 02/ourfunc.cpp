// ourfunc.cpp -- 定义自己的函数
#include <iostream>
void simon(int); // simon()函数的原型声明

int main()
{
    using namespace std;
    simon(3); // 调用simon()函数
    cout << "Pick an integer: ";
    int count;
    cin >> count;
    simon(count); // 再次调用
    cout << "Done!" << endl;
    // cin.get();
    // cin.get();
    return 0;
}

void simon(int n) // 定义simon()函数
{
    using namespace std;

    cout << "Simon says touch your toes " << n << " times." << endl;
} // void函数不需要返回语句
