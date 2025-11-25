#include <iostream>
using namespace std;

int main()
{
	cout << "\\" << endl; // 第一个“\”告诉编译器，使用者要输出一个特殊符号！
	cout << "\tHello" << endl;
	cout << "\n"
		 << endl;

	// 换行符“\n”
	cout << "hello world~\n";

	// 反斜杠“\\”
	cout << "\\" << endl;

	// 水平制表符“\t”，作用：可以整齐地输出数据
	cout << "aaaa\thello world！" << endl;	// “\t”占用8个空格，空格有多长取决于a占用多少字符
	cout << "aa\thello world！" << endl;	// “aaa”占用3个空格，“aaaa”占用4个空格
	cout << "aaaaa\thello world！" << endl; // 水平制表符作用：输出时候的对其效果

	cout << "aaaa hello world！" << endl;
	cout << "aa  hello world！" << endl;
	cout << "aaaaa hello world！" << endl;
	return 0;
}