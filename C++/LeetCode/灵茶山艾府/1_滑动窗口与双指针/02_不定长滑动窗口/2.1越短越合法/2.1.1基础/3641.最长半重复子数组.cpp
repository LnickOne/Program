/*
给定一个长度为 n 的整数数组 nums 和一个整数 k。
半重复子数组是指最多有 k 个元素重复（即出现超过一次）的连续子数组。
返回 nums 中最长 半重复 子数组的长度。
示例 1：
输入：nums = [1,2,3,1,2,3,4], k = 2
输出：6
解释：
最长的半重复子数组是 [2, 3, 1, 2, 3, 4]，其中有 2 个重复元素（2 和 3）。

示例 2：
输入：nums = [1,1,1,1,1], k = 4
输出：5
解释：
最长的半重复子数组是 [1, 1, 1, 1, 1]，其中只有 1 个重复元素（1）。

示例 3：
输入：nums = [1,1,1,1,1], k = 0
输出：1
解释：
最长的半重复子数组是 [1]，其中没有重复元素。
*/
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
class Solution
{
public:
    int longestSubarray(vector<int> &nums, int k)
    {
        int result = 0;
        unordered_map<int, int> numMap;
        int vaild = 0;
        int left = 0;
        for (int right = 0; right < nums.size(); right += 1)
        {
            numMap[nums[right]] += 1;
            if (numMap[nums[right]] == 2)
            {
                vaild += 1;
            }
            while (vaild > k)
            {
                if (numMap[nums[left]] == 2)
                {
                    vaild -= 1;
                }
                numMap[nums[left]] -= 1;
                if (numMap[nums[left]] == 0)
                {
                    numMap.erase(nums[left]);
                }
                left += 1;
            }
            result = max(result, right - left + 1);
        }
        return result;
    }
};
int main()
{
    Solution s;
    vector<int> nums = {1, 2, 3, 1, 2, 3, 4};
    cout << s.longestSubarray(nums, 2) << endl;
    nums = {1, 1, 1, 1, 1};
    cout << s.longestSubarray(nums, 4) << endl;
    cout << s.longestSubarray(nums, 0) << endl;
    nums = {1, 2, 3, 4, 5, 6, 7};
    cout << s.longestSubarray(nums, 0) << endl;
    return 0;
}