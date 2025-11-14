#include <iostream>
using namespace std;

int main()
{
	// continue语句
	for (int i = 0; i < 100; i++)
	{
		if (i % 2 == 0) // 奇数输出，偶数不输出，0 2 4 6 8 10
		{
			continue; // 作用：可以筛选条件，执行到此就不再向下执行；执行下一次循环
					  // break会退出循环，而continue不会
		}
		cout << i << endl;
	}
	return 0;
}