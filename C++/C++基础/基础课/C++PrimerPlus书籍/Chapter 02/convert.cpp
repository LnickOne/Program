// convert.cpp -- 将英石转换为磅
#include <iostream>
int stonetolb(int); // 函数原型声明
int main()
{
    using namespace std;
    int stone;
    cout << "Enter the weight in stone: ";
    cin >> stone;
    int pounds = stonetolb(stone);
    cout << stone << " stone = ";
    cout << pounds << " pounds." << endl;
    // cin.get();
    // cin.get();
    return 0;
}

int stonetolb(int sts)
{
    return 14 * sts;
}
