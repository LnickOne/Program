/*
作用：利用sizeof关键字可以统计数据类型所占内存大小
语法： sizeof( 数据类型 / 变量)
*/
#include <iostream>
using namespace std;
int main()
{
	// 整型：short（2字节）int（4字节）long（4字节）long long（8字节）
	// 可以利用sizeof关键字求出数据类型占用内存大小
	// 语法：sizeof(数据类型 / 变量)
	short num1 = 10;
	cout << "short类型占用内存空间为：" << sizeof(short) << endl;
	cout << "short类型占用内存空间为：" << sizeof(num1) << endl;
	cout << "short 类型所占内存空间为：" << sizeof(short) << endl;
	cout << "int 类型所占内存空间为：" << sizeof(int) << endl;
	cout << "long 类型所占内存空间为：" << sizeof(long) << endl;
	cout << "long long 类型所占内存空间为：" << sizeof(long long) << endl;
	return 0;
}
