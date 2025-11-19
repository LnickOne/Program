#include <iostream>
using namespace std;

int main()
{
	//for循环
	//打印数字0~9
	for (int i = 0; i < 10; i++)
	{
		cout << i << endl;
	}

	//同义拆分
	int i = 0;
	for (;;)
	{
		if (i >= 10)
		{
			break;
		}
		cout << i << endl;
		i++;
	}
	return 0;
}