#include <iostream>
using namespace std;

int main()
{
	// 1、创建bool数据类型
	bool flag = true;	  // true代表真
	cout << flag << endl; // 1

	flag = false;		  // false代表假
	cout << flag << endl; // 0
	// bool本质上，1代表真、0代表假

	// 2、查看bool数据类型所占内存空间
	cout << "bool类型所占内存空间：" << sizeof(bool) << endl; // 1
	cout << "size of bool = " << sizeof(bool) << endl;		  // 1
	return 0;
}