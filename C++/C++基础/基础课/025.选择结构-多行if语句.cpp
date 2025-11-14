#include <iostream>
using namespace std;

int main()
{
	// 选择结构-多行if语句
	// 输入考试分数，如果分数大于600，视为考上一本大学，在屏幕上输出
	// 如果没考上一本大学，打印"未考上一本大学"

	// 1、输入考试分数
	int score = 0;
	cout << "请输入考试分数：" << endl;
	cin >> score;

	// 2、提示用户输入的分数
	cout << "您输入的分数为：" << score << endl;

	// 3、判断如果大于600，打印“考上一本”，否则打印"未考上一本"
	if (score > 600) // 大于600分执行下面大括号中的内容
	{
		cout << "我考上了一本大学！" << endl;
	}
	else // 不大于600分，执行else后大括号中的内容
	{
		cout << "我未考上一本大学！" << endl;
	}
	return 0;
}