/*
给你一个正整数数组 nums ，请你从中删除一个含有 若干不同元素 的子数组。
删除子数组的 得分 就是子数组各元素之 和 。
返回 只删除一个 子数组可获得的 最大得分 。
如果数组 b 是数组 a 的一个连续子序列，
即如果它等于 a[l],a[l+1],...,a[r] ，那么它就是 a 的一个子数组。

示例 1：
输入：nums = [4,2,4,5,6]
输出：17
解释：最优子数组是 [2,4,5,6]

示例 2：
输入：nums = [5,2,1,2,5,2,1,2,5]
输出：8
解释：最优子数组是 [5,2,1] 或 [1,2,5]

提示：
1 <= nums.length <= 105
1 <= nums[i] <= 104
*/
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>
using namespace std;
class Solution
{
public:
  int maximumUniqueSubarray(vector<int> &nums)
  {
    int result = 0;
    int total = 0;
    unordered_map<int, int> numMap;
    int left = 0;
    for (int right = 0; right < nums.size(); right += 1)
    {
      numMap[nums[right]]++;
      total += nums[right];
      while (numMap[nums[right]] > 1)
      {
        numMap[nums[left]]--;
        total -= nums[left];
        left += 1;
      }
      result = max(result, total);
    }
    return result;
  }
};
int main()
{
  vector<int> nums = {4, 2, 4, 5, 6};
  Solution s;
  cout << s.maximumUniqueSubarray(nums) << endl;
  nums = {5, 2, 1, 2, 5, 2, 1, 2, 5};
  cout << s.maximumUniqueSubarray(nums) << endl;
  nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  cout << s.maximumUniqueSubarray(nums) << endl;
  return 0;
}