#include <iostream>
using namespace std;

int main()
{
	// do...while循环语句
	// 在屏幕中输出0~9这10个数字
	int num = 0;
	do
	{
		cout << num << endl;
		num++;
	} while (num < 10);

	num = 0;
	do
	{
		cout << num << endl;
		num++;
	} while (num); // 死循环！！！

	num = 0;
	// while (num < 10 ) // 输出0~9
	while (num) // 不执行任何代码
	{
		cout << num << endl;
		num++;
	}

	// do...while和while循环区别在于do...while会先执行一次循环语句
	return 0;
}