/*
给你一个由 n 个元素组成的整数数组 nums 和一个整数 k 。
请你找出平均数最大且 长度为 k 的连续子数组，并输出该最大平均数。
任何误差小于 10-5 的答案都将被视为正确答案。

示例 1：
输入：nums = [1,12,-5,-6,50,3], k = 4
输出：12.75
解释：最大平均数 (12-5-6+50)/4 = 51/4 = 12.75

示例 2：
输入：nums = [5], k = 1
输出：5.00000
*/
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
class Solution
{
public:
  double findMaxAverage(const vector<int> &nums, int k)
  {
    double result = 0;
    double sum = 0;
    // 处理第一个窗口
    for (int i = 0; i < k; i += 1)
    {
      sum += nums[i];
    }
    result = sum / k;
    // 处理后续窗口
    for (int i = k; i < nums.size(); i += 1)
    {
      sum += nums[i];
      sum -= nums[i - k];
      result = max(result, sum / k);
    }
    return result;
  }
};
int main()
{
  Solution s;
  cout << s.findMaxAverage(vector<int>{1, 12, -5, -6, 50, 3}, 4) << endl;
  cout << s.findMaxAverage(vector<int>{5}, 1) << endl;
  cout << s.findMaxAverage(vector<int>{-1}, 1) << endl;
  cout << s.findMaxAverage(vector<int>{0, 4, 0, 3, 2}, 1) << endl;
  cout << s.findMaxAverage(vector<int>{0, 4, 0, 3, 2}, 2) << endl;
  return 0;
}
