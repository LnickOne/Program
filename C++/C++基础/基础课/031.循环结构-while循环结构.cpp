#include <iostream>
using namespace std;

int main()
{
	// while循环
	// 在屏幕上打印 0 ~ 9 这10个数字
	int num = 0;
	// while()中填入循环条件
	// 注意事项：在写循环时，一定要避免死循环的出现。while (1)死循环
	while (num < 10)
	{ // 循环代码
		cout << "num = " << num << endl;
		num++;
	}
	return 0;
}