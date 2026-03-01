/*
给你一个长度为 n 的整数数组 nums 与一个整数 k。
你的任务是找到 nums 所有 长度为 k的子数组中 不同 元素的数量。
返回一个数组 ans，其中 ans[i] 是对于每个索引 0 <= i < n - k，nums[i..(i + k -1)]
中不同元素的数量。 示例 1: 输入: nums = [1,2,3,2,2,1,3], k = 3 输出: [3,2,2,2,3]
解释：每个子数组的数字种类计算方法如下：
- nums[0..2] = [1,2,3] 所以 ans[0] = 3
- nums[1..3] = [2,3,2] 所以 ans[1] = 2
- nums[2..4] = [3,2,2] 所以 ans[2] = 2
- nums[3..5] = [2,2,1] 所以 ans[3] = 2
- nums[4..6] = [2,1,3] 所以 ans[4] = 3
示例 2:
输入: nums = [1,1,1,1,2,3,4], k = 4
输出: [1,2,3,4]
解释: 每个子数组的数字种类计算方法如下：
- nums[0..3] = [1,1,1,1] 所以 ans[0] = 1
- nums[1..4] = [1,1,1,2] 所以 ans[1] = 2
- nums[2..5] = [1,1,2,3] 所以 ans[2] = 3
- nums[3..6] = [1,2,3,4] 所以 ans[3] = 4
*/
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
class Solution
{
public:
  vector<int> distinctNumbers(vector<int> &nums, int k)
  {
    vector<int> result(nums.size() - k + 1);
    unordered_map<int, int> numMap;
    // 处理第一个窗口
    for (int i = 0; i < k; i += 1)
    {
      numMap[nums[i]] += 1;
    }
    result[0] = numMap.size();
    // 处理后续窗口
    for (int i = k; i < nums.size(); i += 1)
    {
      numMap[nums[i]] += 1;
      numMap[nums[i - k]] -= 1;
      if (numMap[nums[i - k]] == 0)
        numMap.erase(nums[i - k]);
      result[i - k + 1] = numMap.size();
    }
    return result;
  }
};
int main()
{
  Solution s;
  vector<int> nums = {1, 2, 3, 2, 2, 1, 3};
  vector<int> result = s.distinctNumbers(nums, 3);
  for (int i = 0; i < result.size(); i += 1)
  {
    cout << result[i] << " ";
  }
  cout << endl;
  vector<int> nums1 = {1, 1, 1, 1, 2, 3, 4};
  vector<int> result1 = s.distinctNumbers(nums1, 4);
  for (int i = 0; i < result1.size(); i += 1)
  {
    cout << result1[i] << " ";
  }
  cout << endl;
  return 0;
}