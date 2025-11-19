#include <iostream>
using namespace std;

int main() // 赋值运算符
{
	// =
	int a = 10;
	a = 100;
	cout << "a = " << a << endl; // a = 100

	// +=
	a = 10;
	a += 2;						 // a = a + 2;
	cout << "a = " << a << endl; // a = 12

	// -=
	a = 10;
	a -= 2;						 // a = a - 2
	cout << "a = " << a << endl; // a = 8

	// *=
	a = 10;
	a *= 2;						 // a = a * 2
	cout << "a = " << a << endl; // a = 20

	// /=
	a = 10;
	a /= 2;						 // a = a / 2;
	cout << "a = " << a << endl; // a = 5

	// %=
	a = 10;
	a %= 2;						 // a = a % 2;
	cout << "a = " << a << endl; // a = 0
	return 0;
}