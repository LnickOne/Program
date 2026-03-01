/*
你是一个专业的小偷，计划偷窃沿街的房屋。
每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。

示例 1：
输入：[1,2,3,1]
输出：4
解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
     偷窃到的最高金额 = 1 + 3 = 4 。
示例 2：
输入：[2,7,9,3,1]
输出：12
解释：偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
     偷窃到的最高金额 = 2 + 9 + 1 = 12 。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
    // 递推法
    int rob(vector<int> &nums)
    {
        if (nums.empty())
            return 0;
        if (nums.size() == 1)
            return nums[0];
        // dp[i]:表示不触动警报装置的情况下,从(0,...,i)房屋偷窃到的最高金额为dp[i]
        vector<int> dp(nums.size());
        dp[0] = nums[0];
        dp[1] = max(nums[1], nums[0]);
        // 递推公式 dp[i]=max(dp[i-1],dp[i-2]+nums[i])
        // 抵达下标i后，不偷nums[i](即dp[i-1](0,...,i-1)偷到的金额和偷nums[i](即dp[i-2](0,...,i-1)+nums[i])(要间隔一间房子才能偷nums[i])
        for (int i = 2; i < nums.size(); i += 1)
        {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        return *max_element(dp.begin(), dp.end());
    }
    // 记忆化搜索法
    int rob_memory(vector<int> &nums)
    {
        int result = 0;
        vector<int> memory(nums.size(), -1);
        result = dfs(nums.size() - 1, nums, memory);
        return result;
    }
    int dfs(int i, vector<int> &nums, vector<int> &memory)
    {
        if (i < 0)
        {
            return 0;
        }
        if (memory[i] != -1)
        {
            return memory[i];
        }
        memory[i] = max(dfs(i - 1, nums, memory), dfs(i - 2, nums, memory) + nums[i]);
        return memory[i];
    }
};
int main()
{
    Solution s;
    vector<int> nums{1, 2, 3, 1};
    vector<int> nums1{2, 3, 2};
    vector<int> nums2{1, 2, 3};
    vector<int> nums3{1, 2, 3, 4, 5, 6, 7};
    cout << s.rob(nums) << endl;
    cout << s.rob(nums1) << endl;
    cout << s.rob(nums2) << endl;
    cout << s.rob(nums3) << endl;
    return 0;
}