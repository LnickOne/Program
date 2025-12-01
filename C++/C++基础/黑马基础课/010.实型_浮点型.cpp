#include <iostream>
using namespace std;

int main()
{
	float f1 = 3.1415926f; // 1、单精度 float
	double d1 = 3.1415926; // 2、双精度 double

	// 默认情况下，输出一个小数，会显示出6位有效数字
	cout << f1 << endl; // 小数，最多6位有效数字
	cout << d1 << endl;

	// 统计float和double占用内存空间
	cout << "float占用内存空间为：" << sizeof(float) << endl;	// 4字节
	cout << "double占用内存空间为：" << sizeof(double) << endl; // 8字节
	cout << "float  sizeof = " << sizeof(f1) << endl;
	cout << "double sizeof = " << sizeof(d1) << endl;

	// 科学计数法
	float f2 = 3e2; // 3 * 10 ^ 2
	cout << "f2 = " << f2 << endl;

	float f3 = 3e-2; // 3 * 0.1 ^ 2
	cout << "f3 = " << f3 << endl;
	return 0;
}