// getinfo.cpp -- 输入和输出
#include <iostream>

int main()
{
    using namespace std;

    int carrots;

    cout << "How many carrots do you have?" << endl;
    cin >> carrots; // C++输入
    cout << "Here are two more. ";
    carrots = carrots + 2;
    // 下一行连接输出内容
    cout << "Now you have " << carrots << " carrots." << endl;
    // cin.get();
    // cin.get();
    return 0;
}
