#include <iostream>
#include <string> //string头文件
using namespace std;

int main()
{
	// 1、整型 输入
	int a = 0;
	cout << "请给整型变量a赋值：" << endl; // 请输入整型变量
	cin >> a;
	cout << "整型变量a = " << a << endl;

	// 2、浮点型 输入
	double d = 0;
	cout << "请给浮点型变量d赋值：" << endl; // 请输入浮点型变量
	cin >> d;								 // “>>”右移运算符
	cout << "浮点型变量d = " << d << endl;

	float f = 3.14f;
	cout << "请给浮点型变量f赋值：" << endl; // 请输入浮点型变量
	cin >> f;
	cout << "浮点型变量f = " << f << endl;

	// 3、字符型 输入
	char ch = 0;
	cout << "请给字符型变量ch赋值：" << endl; // 请输入字符型变量
	cin >> ch;
	cout << "字符型变量ch = " << ch << endl;

	// 4、字符串型 输入
	string str;
	cout << "请给字符串型变量str赋值：" << endl; // 请输入字符串型变量
	cin >> str;
	cout << "字符串型变量str = " << str << endl;

	// 5、布尔类型 输入
	bool flag = true;
	cout << "请给布尔型变量flag赋值：" << endl; // 请输入布尔型变量
	cin >> flag;								// bool类型：只要是非0的值，都代表真
	cout << "布尔型变量flag = " << flag << endl;
	return EXIT_SUCCESS;
}