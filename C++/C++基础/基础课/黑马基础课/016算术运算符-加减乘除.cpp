#include <iostream>
using namespace std;

int main()
{
	int a1 = 10;
	int b1 = 3;

	cout << a1 + b1 << endl; // 13
	cout << a1 - b1 << endl; // 7
	cout << a1 * b1 << endl; // 30
	cout << a1 / b1 << endl; // 3 两个整数相除,结果依然是整数,将小数部分去除

	int a2 = 10;
	int b2 = 20;
	cout << a2 / b2 << endl; // 0

	int a3 = 10;
	int b3 = 0;
	// 错误！两个数相除，除数不可以为0！
	// cout << a3 / b3 << endl; //报错，除数不可以为0。

	// 两个小数可以相除
	double d1 = 0.5;
	double d2 = 0.25;
	cout << d1 / d2 << endl; // 2 运算结果可以是整数

	d1 = 0.5;
	d2 = 0.22;
	cout << d1 / d2 << endl; // 2.27273 运算结果可以是小数
	return 0;
}