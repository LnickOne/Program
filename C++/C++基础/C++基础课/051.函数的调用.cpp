#include <iostream>
using namespace std;

// 函数定义：定义加法函数
// 函数定义的时候，num1和num2并没有真实数据，它只是一个形式上的参数，简称形参
int add(int num1, int num2) // 参数列表（形参列表）定义中的num1,num2称为形式参数，简称形参
{
	int sum = num1 + num2;
	return sum;
}

int main()
{
	// mian函数中调用add函数
	int a = 10;
	int b = 10;
	// 函数调用语法：函数名称(参数) 当调用函数的时候，实参的值会传递给形参
	int sum = add(a, b); // 调用时的a、b称为实际参数，简称实参
	cout << "sum = " << sum << endl;

	a = 100;
	b = 100;
	sum = add(a, b);
	cout << "sum = " << sum << endl;
	return 0;
}