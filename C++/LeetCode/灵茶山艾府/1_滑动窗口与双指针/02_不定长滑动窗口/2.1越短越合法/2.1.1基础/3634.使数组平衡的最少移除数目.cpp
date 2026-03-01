/*
给你一个整数数组 nums 和一个整数 k。
如果一个数组的 最大 元素的值 至多 是其 最小 元素的 k倍，则该数组被称为是平衡的。 
你可以从 nums 中移除 任意数量的元素，但不能使其变为 空 数组。
返回为了使剩余数组平衡，需要移除的元素的最小数量。 
注意：大小为 1的数组被认为是平衡的，因为其最大值和最小值相等，且条件总是成立。

示例 1:
输入：nums = [2,1,5], k = 2
输出：1
解释：
移除 nums[2] = 5 得到 nums = [2, 1]。
现在 max = 2, min = 1，且 max <= min * k，因为 2 <= 1 * 2。因此，答案是 1。

示例 2:
输入：nums = [1,6,2,9], k = 3
输出：2
解释：
移除 nums[0] = 1 和 nums[3] = 9 得到 nums = [6, 2]。
现在 max = 6, min = 2，且 max <= min * k，因为 6 <= 2 * 3。因此，答案是 2。

示例 3:
输入：nums = [4,6], k = 2
输出：0
解释：
由于 nums 已经平衡，因为 6 <= 4 * 2，所以不需要移除任何元素。

思路：
我们只关心剩余元素的最小值和最大值，不关心元素的顺序，所以可以先从小到大排序，方便后续计算。
排序后，枚举最大值 max=nums[right]，那么最小值 min=nums[left] 必须满足min*k≥max
如果不满足，由于我们排序了，可以把 left 加一，直到满足上式。
可见，随着 right 的增大，left 要么不变，要么也增大
用窗口长度 right−left+1 更新保留元素个数的窗口最大值 max_len
最终答案为 nums.size()-max_len
*/
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  int minRemoval(vector<int> &nums, int k)
  {
    if (nums.size() == 1)
      return 0;
    sort(nums.begin(), nums.end());
    int result = 0;
    int left = 0;
    int max_len = 0;
    for (int right = 0; right < nums.size(); right += 1)
    {
      long maxNum = nums[right];
      long minNum = nums[left];
      if (minNum * k < maxNum)
      {
        left += 1;
      }
      max_len = max(max_len, right - left + 1);
    }
    return nums.size() - max_len;
  }
};
int main()
{
  Solution s;
  vector<int> nums = {4, 6};
  int k = 2;
  cout << s.minRemoval(nums, k) << endl;
  nums = {1, 6, 2, 9};
  k = 3;
  cout << s.minRemoval(nums, k) << endl;
  nums = {2, 1, 5};
  k = 2;
  cout << s.minRemoval(nums, k) << endl;
  return 0;
}