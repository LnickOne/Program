#include <iostream>
using namespace std;

// 提前告诉编译器函数的存在（可以利用函数的声明）
// 函数的声明（无具体的代码实现）
// 声明可以写多次，但是定义只能有一次
int max(int a, int b);
int max(int a, int b);
int max(int a, int b);

int main()
{
	int a = 100;
	int b = 200;
	cout << max(a, b) << endl; // 200
	return 0;
}

// 定义（函数的声明）
// 比较函数，实现两个整型数字进行比较，返回较大的值
int max(int a, int b)
{
	return a > b ? a : b;
}
// 下面是错的，定义只能有一次！
// int max(int a, int b)
// {
// 	return a > b ? a : b;
// }