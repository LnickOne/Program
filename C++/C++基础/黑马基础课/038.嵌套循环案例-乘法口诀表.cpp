#include <iostream>
using namespace std;

int main()
{
	// 乘法口诀表
	for (int i = 1; i <= 9; i++) // 打印行数
	{
		// cout << i << endl;
		for (int j = 1; j <= i; j++) // 打印列数
		{
			cout << j << "*" << i << "=" << i * j << "  ";
		}
		cout << endl;
	}
	return 0;
}