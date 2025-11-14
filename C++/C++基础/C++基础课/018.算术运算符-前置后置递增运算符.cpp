#include <iostream>
using namespace std;

int main() // 递增
{
	// 1、前置递增
	int a = 10;
	++a;						 // 让变量+1
	cout << "a = " << a << endl; // 11

	// 2、后置递增
	int b = 10;
	b++;			   // 让变量+1,等价于b = b + 1
	cout << b << endl; // 11

	// 3、前值和后置的区别
	// 前置递增：先对变量进行++，再计算表达式
	int a2 = 10;
	int b2 = ++a2 * 10;
	cout << "a2 = " << a2 << endl; // 11
	cout << "b2 = " << b2 << endl; // 11 * 10 -> 110

	// 后置递增：先计算表达式，后对变量进行++
	int a3 = 10;
	int b3 = a3++ * 10;
	cout << "a3 = " << a3 << endl; // 11
	cout << "b3 = " << b3 << endl; // 100
	return 0;
}