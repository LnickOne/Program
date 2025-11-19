#include <iostream>
using namespace std;

int main()
{
	// 1、先输出1~100数字
	for (int i = 1; i <= 100; i++)
	{
		// 2、从100个数中找到特殊的数字，打印“敲桌子！”
		// 如果是7的倍数、个位是7、十位是7，打印“敲桌子！”
		if (i % 7 == 0 || i % 10 == 7 || i / 10 == 7) // 如果是特殊数字，打印“敲桌子！”
		{
			cout << "敲桌子！" << endl;
		}
		else // 如果不是特殊数字，打印数字
		{
			cout << i << endl;
		}
	}
	return 0;
}