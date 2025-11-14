#include <iostream>
using namespace std;

int main()
{
	int a1 = 10;
	int b1 = 3;
	cout << a1 % b1 << endl; // 1

	int a2 = 10;
	int b2 = 20;
	cout << a2 % b2 << endl; // 10

	int a3 = 10;
	int b3 = 0;
	// 两个数相除，除数不可以为0，所以做不了取模运算
	//  cout << a3 % b3 << endl; // 报错。取模运算时，除数不能为0！

	// 两个小数是不可以做取模运算的
	double d1 = 3.14;
	double d2 = 1.1;
	// cout << d1 % d2 << endl; // 报错
	return 0;
}