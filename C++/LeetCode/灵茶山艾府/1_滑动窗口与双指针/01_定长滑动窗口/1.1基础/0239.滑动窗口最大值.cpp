/*
给你一个整数数组 nums，有一个大小为 k
的滑动窗口从数组的最左侧移动到数组的最右侧。 你只可以看到在滑动窗口内的 k
个数字。 滑动窗口每次只向右移动一位。 返回 滑动窗口中的最大值 。 示例 1：
输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
输出：[3,3,5,5,6,7]
解释：
滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
示例 2：
输入：nums = [1], k = 1
输出：[1]
*/
#include <algorithm>
#include <deque>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
class Solution
{
public:
  vector<int> maxSlidingWindow(vector<int> &nums, int k)
  {
    if (nums.empty() || k <= 0)
    {
      return {};
    }
    if (k > nums.size())
    {
      return {*max_element(nums.begin(), nums.end())};
    }
    if (nums.size() == 1)
    {
      return nums;
    }
    vector<int> result;
    int max_num;
    // 处理第一个窗口
    max_num = *max_element(nums.begin(), nums.begin() + k);
    result.emplace_back(max_num);
    // 处理后续窗口
    for (int i = k; i < nums.size(); i += 1)
    {
      if (nums[i - k] == max_num)
      {
        max_num = *max_element(nums.begin() + i - k + 1, nums.begin() + i + 1);
      }
      else
      {
        if (nums[i] > max_num)
        {
          max_num = nums[i];
        }
      }
      result.emplace_back(max_num);
    }
    return result;
  }
};

int main()
{
  Solution s;
  vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
  int k = 3;
  vector<int> nums1 = {1, 3, -1, -3, 5, 3, 6, 7};
  int k1 = 5;
  vector<int> result = s.maxSlidingWindow(nums, k);
  for (int i = 0; i < result.size(); i++)
  {
    cout << result[i] << " ";
  }
  cout << endl;
  vector<int> result1 = s.maxSlidingWindow(nums1, k1);
  for (int i = 0; i < result1.size(); i++)
  {
    cout << result1[i] << " ";
  }
  cout << endl;
  return 0;
}