#include <iostream>
#include <ctime> // time系统时间头文件
using namespace std;

int main()
{
	// 添加随机数种子，作用：利用当前系统时间生成随机数，防止每次随机数都是一样。
	srand((unsigned int)time(NULL));

	// 1、系统生成随机数【rand() % 100：生成0~99的随机数】
	int num = rand() % 100 + 1; // rand()%100+1 生成 0+1 ~ 99+1 的随机数
	cout << "系统生成随机数(0~99)：" << num << endl;

	// 2、玩家进行猜数
	int val = 0; // 玩家输入数据

	while (1) // 死循环
	{
		cin >> val;

		// 3、判断玩家的猜测
		// 猜错：提示猜的结果 过大或过小，重新返回第二步
		if (val > num)
		{
			cout << "猜测过大！\n"
				 << endl;
		}
		else if (val < num)
		{
			cout << "猜测过小！\n"
				 << endl;
		}
		else
		{
			cout << "猜测正确！\n"
				 << endl;
			// 猜对：退出游戏
			break; // break, 可以利用该关键字退出当前循环。
		}
	}
	return 0;
}