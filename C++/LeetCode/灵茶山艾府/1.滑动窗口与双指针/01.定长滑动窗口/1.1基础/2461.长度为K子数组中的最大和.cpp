/*
给你一个整数数组 nums 和一个整数 k 。请你从 nums 中满足下述条件的全部子数组中找出最大子数组和：
子数组的长度是 k，且子数组中的所有 元素 各不相同 。
返回满足题面要求的最大子数组和。
如果不存在子数组满足这些条件，返回 0 。
子数组 是数组中一段连续非空的元素序列。

示例 1：
输入：nums = [1,5,4,2,9,9,9], k = 3
输出：15
解释：nums 中长度为 3 的子数组是：
- [1,5,4] 满足全部条件，和为 10 。
- [5,4,2] 满足全部条件，和为 11 。
- [4,2,9] 满足全部条件，和为 15 。
- [2,9,9] 不满足全部条件，因为元素 9 出现重复。
- [9,9,9] 不满足全部条件，因为元素 9 出现重复。
因为 15 是满足全部条件的所有子数组中的最大子数组和，所以返回 15 。

示例 2：
输入：nums = [4,4,4], k = 3
输出：0
解释：nums 中长度为 3 的子数组是：
- [4,4,4] 不满足全部条件，因为元素 4 出现重复。
因为不存在满足全部条件的子数组，所以返回 0 。
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
class Solution
{
public:
    long long maximumSubarraySum(vector<int> &nums, int k)
    {
        if (nums.size() < k)
            return 0;
        long long sum = 0;
        vector<long long> result;
        unordered_map<long long, int> cntMap;
        // 处理第一个窗口
        for (int i = 0; i < k; i += 1)
        {
            sum += nums[i];
            cntMap[nums[i]] += 1;
            if (cntMap.size() == k)
            {
                result.push_back(sum);
            }
        }
        // 处理后续窗口
        for (int i = k; i < nums.size(); i += 1)
        {
            // 处理窗口，先删除窗口第一个元素，再添加窗口最后一个元素
            cntMap[nums[i - k]] -= 1;
            if (cntMap[nums[i - k]] == 0)
            {
                cntMap.erase(nums[i - k]);
            }
            cntMap[nums[i]] += 1;
            sum += nums[i];
            sum -= nums[i - k];
            if (cntMap.size() == k)
            {
                result.push_back(sum);
            }
        }
        if (result.empty())
            return 0;
        else
            return (*max_element(result.begin(), result.end()));
    }
};
int main()
{
    Solution s;
    vector<int> nums = {1, 5, 4, 2, 9, 9, 9};
    int k = 3;
    cout << s.maximumSubarraySum(nums, k) << endl;
    nums = {4, 4, 4};
    k = 3;
    cout << s.maximumSubarraySum(nums, k) << endl;
    nums = {1, 1, 1, 7, 8, 9};
    k = 3;
    cout << s.maximumSubarraySum(nums, k) << endl;
    nums = {5, 9, 9, 2, 4, 5, 4};
    k = 3;
    cout << s.maximumSubarraySum(nums, k) << endl;
    return 0;
}