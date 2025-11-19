#include <iostream>
using namespace std;

int main()
{
	// 二维数组数组名
	int arr[2][3] = {{1, 2, 3}, {4, 5, 6}};

	// 1、可以查看占用内存空间大小
	cout << "=== 内存空间大小 ===" << endl;
	cout << "二维数组总大小为：" << sizeof(arr) << " 字节" << endl;				  // 24
	cout << "二维数组第一行大小为：" << sizeof(arr[0]) << " 字节" << endl;		  // 12
	cout << "二维数组第一个元素大小为：" << sizeof(arr[0][0]) << " 字节" << endl; // 4

	cout << "二维数组行数为：" << sizeof(arr) / sizeof(arr[0]) << endl;		  // 2
	cout << "二维数组列数为：" << sizeof(arr[0]) / sizeof(arr[0][0]) << endl; // 3

	// 2、可以查看二维数组的首地址
	cout << "=== 地址信息（十六进制）===" << endl;
	cout << "二维数组首地址为：" << arr << endl;
	cout << "二维数组第一行地址：" << arr[0] << endl;
	cout << "二维数组第二行地址：" << arr[1] << endl; // 第一二行相差12字节（3个int）

	cout << "=== 地址信息（十进制）===" << endl;
	cout << "二维数组首地址为：" << (long long)arr << endl;
	cout << "二维数组第一行地址：" << (long long)arr[0] << endl;
	cout << "二维数组第二行地址：" << (long long)arr[1] << endl;

	cout << "=== 元素地址 ===" << endl;
	cout << "第一个元素地址：" << &arr[0][0] << " (十进制: " << (long long)&arr[0][0] << ")" << endl;
	cout << "第二个元素地址：" << &arr[0][1] << " (十进制: " << (long long)&arr[0][1] << ")" << endl;
	cout << "第二个元素与第一个元素地址差：" << (long long)&arr[0][1] - (long long)&arr[0][0] << " 字节" << endl;
	return 0;
}