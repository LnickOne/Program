#include <iostream>
#include <string>
using namespace std;

int main() // 二维数组案例-考试成绩统计
{
	// 1、创建二维数组
	int scores[3][3] = {
		{100, 100, 100}, // 张三
		{90, 50, 100},	 // 李四
		{60, 70, 80}	 // 王五
	};
	// 存放姓名的字符串一维数组
	string names[3] = {"张三", "李四", "王五"};

	// 2、统计每个人的总和分数
	for (int i = 0; i < 3; i++) // 行
	{
		int sum = 0;				// 统计分数总和
		for (int j = 0; j < 3; j++) // 列
		{
			sum += scores[i][j];
			// cout << scores[i][j] << " ";
		}
		// cout << endl;
		// cout << "第" << i + 1 << "个人的总分为：" << sum << " ！" << endl;
		cout << names[i] << "同学的总成绩为：" << sum << " ！" << endl;
	}
	return 0;
}