/*
有一个书店老板，他的书店开了 n 分钟。
每分钟都有一些顾客进入这家商店。
给定一个长度为 n 的整数数组 customers ，其中 customers[i] 是在第 i
分钟开始时进入商店的顾客数量，所有这些顾客在第 i 分钟结束后离开。
在某些分钟内，书店老板会生气。
如果书店老板在第 i 分钟生气，那么 grumpy[i] = 1，否则 grumpy[i] = 0。
当书店老板生气时，那一分钟的顾客就会不满意，若老板不生气则顾客是满意的。
书店老板知道一个秘密技巧，能抑制自己的情绪，
可以让自己连续minutes分钟不生气，但却只能使用一次。
请你返回这一天营业下来，最多有多少客户能够感到满意。

示例 1：
输入：customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], minutes = 3
输出：16
解释：书店老板在最后 3 分钟保持冷静。
感到满意的最大客户数量 = 1 + 1 + 1 + 1 + 7 + 5 = 16.

示例 2：
输入：customers = [1], grumpy = [0], minutes = 1
输出：1
*/
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  int maxSatisfied(vector<int> &customers, vector<int> &grumpy, int minutes)
  {
    int result = 0;
    int k = minutes;
    int normalSum = 0;
    // 老板按照正常生气规律所能获得所有顾客最大的满意度(计算的是下标为0的)，
    // 一般偏小，因为恰好有最大满意度的顾客刚好在老板生气的时间
    for (int i = 0; i < customers.size(); i += 1)
    {
      if (grumpy[i] == 0)
      {
        normalSum += customers[i];
      }
    }
    // 处理第一个窗口老板使用不生气技巧获得额外满意度
    int extraSum = 0;
    int maxExtra = 0; // 记录所有窗口中额外满意度的最大值,这个额外值加上正常满意度就是最大满意度
    for (int i = 0; i < k; i += 1)
    {
      if (grumpy[i] == 1)
      {
        extraSum += customers[i];
      }
    }
    maxExtra = extraSum;
    // 更新后续窗口，依次计算每个窗口的额外满意度，取最大值
    for (int i = k; i < customers.size(); i += 1)
    {
      if (grumpy[i] == 1)
      {
        extraSum += customers[i];
      }
      if (grumpy[i - k] == 1)
      {
        extraSum -= customers[i - k];
      }
      maxExtra = max(maxExtra, extraSum);
    }
    return normalSum + maxExtra;
  }
};
int main()
{
  vector<int> customers = {1, 0, 1, 2, 1, 1, 7, 5};
  vector<int> grumpy = {0, 1, 0, 1, 0, 1, 0, 1};
  int minutes = 3;
  Solution s;
  cout << s.maxSatisfied(customers, grumpy, minutes) << endl;
  customers = {4, 10, 10};
  grumpy = {1, 1, 0};
  minutes = 2;
  cout << s.maxSatisfied(customers, grumpy, minutes) << endl;
  return 0;
}