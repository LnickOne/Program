/*
你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。
这个地方所有的房屋都 围成一圈 ，这意味着第一个房屋和最后一个房屋是紧挨着的。
同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警 。
给定一个代表每个房屋存放金额的非负整数数组，计算你 在不触动警报装置的情况下 ，今晚能够偷窃到的最高金额。
示例 1：
输入：nums = [2,3,2]
输出：3
解释：你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）,因为他们是相邻的。
示例 2：
输入：nums = [1,2,3,1]
输出：4
解释：你可以先偷窃 1 号房屋（金额 = 1），然后偷窃 3 号房屋（金额 = 3）。偷窃到的最高金额 = 1 + 3 = 4 。
示例 3：
输入：nums = [1,2,3]
输出：3
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
    /*
    动态规划五部曲(递推法)
    1. 确定dp数组以及下标的含义
    dp[i]表示在不触动警报装置的情况下，能够在下标[0,i-1]的范围内偷窃到的最高金额
    2. 确定递推关系 整体递推关系是这样
    dp[i]的最大金额的状态是由 dp[i-1]不偷nums[i]的金额，和dp[i-2]+nums[i]偷nums[i]的金额互相比较出最大值推导出来。
    dp[i] = max(dp[i-2]+nums[i],dp[i-1])
    有三种情况
    不考虑首尾元素
    考虑首元素,不考虑尾元素
    考虑尾元素,不考虑首元素
    最后求三种情况分别得到的值中的最大值
    3. 确定初始值
    dp[0] = nums[0]
    dp[1] = max(nums[0],nums[1])
    4. 确定遍历顺序
    for(int i=2;i<nums.size();i++)
        dp[i] = max(dp[i-2]+nums[i],dp[i-1])
    */
    int rob(vector<int> &nums)
    {
        if (nums.empty())
            return 0;
        if (nums.size() == 1)
            return nums[0];
        vector<int> nums_1(nums.begin() + 1, nums.end() - 1); // 不考虑首尾元素
        vector<int> nums_2(nums.begin(), nums.end() - 1);     // 考虑首元素不考虑尾元素
        vector<int> nums_3(nums.begin() + 1, nums.end());     // 考虑尾元素不考虑首元素
        return max(rob_condition(nums_1), max(rob_condition(nums_2), rob_condition(nums_3)));
    }
    int rob_condition(vector<int> &nums)
    {
        if (nums.empty())
            return 0;
        if (nums.size() == 1)
            return nums[0];
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); i += 1)
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        return *max_element(dp.begin(), dp.end());
    }
    // 记忆化搜索法
    int rob_momory(vector<int> &nums)
    {
        if (nums.size() == 0)
            return 0;
        if (nums.size() == 1)
            return nums[0];
        int result1 = 0, result2 = 0, result3 = 0;
        vector<int> nums_1(nums.begin() + 1, nums.end() - 1); // 不考虑首尾元素
        vector<int> nums_2(nums.begin(), nums.end() - 1);     // 考虑首元素不考虑尾元素
        vector<int> nums_3(nums.begin() + 1, nums.end());     // 考虑尾元素不考虑首元素

        // 情况1：不考虑首尾元素
        if (!nums_1.empty())
        {
            vector<int> memory1(nums_1.size(), -1);
            result1 = dfs(nums_1.size() - 1, nums_1, memory1);
        }

        // 情况2：考虑首元素不考虑尾元素
        if (!nums_2.empty())
        {
            vector<int> memory2(nums_2.size(), -1);
            result2 = dfs(nums_2.size() - 1, nums_2, memory2);
        }

        // 情况3：考虑尾元素不考虑首元素
        if (!nums_3.empty())
        {
            vector<int> memory3(nums_3.size(), -1);
            result3 = dfs(nums_3.size() - 1, nums_3, memory3);
        }

        return max(result1, max(result2, result3));
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
        memory[i] = max(dfs(i - 2, nums, memory) + nums[i], dfs(i - 1, nums, memory));
        return memory[i];
    }
};
int main()
{
    Solution s;
    vector<int> nums{1, 2, 3, 1};
    vector<int> nums1{2, 3, 2};
    vector<int> nums2{1, 2, 3};
    cout << s.rob(nums) << endl;
    cout << s.rob(nums1) << endl;
    cout << s.rob(nums2) << endl;
    return 0;
}