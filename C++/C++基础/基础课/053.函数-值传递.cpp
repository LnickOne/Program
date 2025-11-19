#include <iostream>
using namespace std;
// 值传递
// 定义函数，实现两个数字进行交换的函数

// 如果函数不需要返回值，声明的时候可以写void
void swap(int num1, int num2)
{
	cout << "交换前：" << endl;
	cout << "num1 = " << num1 << endl;
	cout << "num2 = " << num2 << endl;

	int temp = num1; // 数据交换
	num1 = num2;
	num2 = temp;

	cout << "交换后：" << endl;
	cout << "num1 = " << num1 << endl;
	cout << "num2 = " << num2 << endl;
	// return ; 当函数声明时候，返回值不需要的时候，可以不写return
}

int main()
{
	int a = 10; // 创建变量a的时候，在内存中开辟4个字节给变量a
	int b = 20;

	cout << "mian中的 a = " << a << endl;
	cout << "mian中的 b = " << b << endl;

	// 当我们做值传递的时候，函数的形参发生改变，并不会影响实参！
	swap(a, b); // 调用函数体时，需要分配空间给num1、num2，与a、b不是同一个东西

	cout << "mian中的 a = " << a << endl;
	cout << "mian中的 b = " << b << endl;
	return 0;
}