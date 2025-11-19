#include <iostream>
using namespace std;

int main()
{
	// 利用嵌套循环实现星图
	// 外层循环执行1次，内层循环执行1轮（1周）
	for (int i = 0; i < 10; i++) // 外层循环：打印一行星图
	{
		for (int j = 0; j < 10; j++) // 内层循环：打印一行*
		{
			cout << "*"
				 << " "; //*加空格
		}
		cout << endl; // 换行
	}
	return 0;
}