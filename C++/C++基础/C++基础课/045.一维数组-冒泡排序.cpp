#include <iostream>
using namespace std;

int main() // 利用冒泡排序实现升序序列
{
	int arr[9] = {4, 2, 8, 0, 5, 7, 1, 3, 9};

	// 打印排序前的数字
	cout << "排序前：" << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << arr[i] << "  ";
	}
	cout << endl;

	// 开始冒泡排序
	// 总共排序轮次 = 元素个数 — 1
	for (int i = 0; i < 9 - 1; i++)
	{
		// 内层循环对比：次数 = 元素个数 - 当前轮次 - 1
		for (int j = 0; j < 9 - 1 - i; j++)
		{
			// 如果第一个数字比第二个数字大，交换数字
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j]; // 实现两个元素的交换
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	// 打印排序后的结果
	cout << "排序后：" << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << arr[i] << "  ";
	}
	cout << endl;
	return 0;
}