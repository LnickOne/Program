// carrots.cpp -- 食品处理程序
// 使用并显示变量

#include <iostream>
using namespace std;
int main()
{
    int carrots;  // 声明一个整型变量
    carrots = 25; // 给变量赋值
    cout << "I have ";
    cout << carrots; // display the value of the variable
    cout << " carrots.";
    cout << endl;
    carrots = carrots - 1; // 修改变量的值
    cout << "Crunch, crunch. Now I have " << carrots << " carrots." << endl;
    // cin.get();
    return 0;
}
