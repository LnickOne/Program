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
	cout << "string类型所占内存空间为：" << sizeof(string) << endl;
	return 0;
}
/*
数据类型 32位系统 64位系统 占用空间
char	1 字节	1 字节	1 字节
bool	1 字节	1 字节	1 字节
short	2 字节	2 字节	2 字节
int	    4 字节	4 字节	4 字节
long	4 字节	8 字节	4 字节 / 8 字节
float	4 字节	4 字节	4 字节
double	8 字节	8 字节	8 字节
unsigned char	1 字节	1 字节	1 字节
unsigned short	2 字节	2 字节	2 字节
unsigned int	4 字节	4 字节	4 字节
unsigned long	4 字节	8 字节	4 字节 / 8 字节
指针	 4 字节	8 字节	4 字节 / 8 字节
wchar_t	2 字节	4 字节	2 字节 / 4 字节
size_t	4 字节	8 字节	4 字节 / 8 字节
ptrdiff_t	4 字节	8 字节	4 字节 / 8 字节
string	取决于内容长度	取决于内容长度	动态分配 64位linux下，string占用32字节
*/
