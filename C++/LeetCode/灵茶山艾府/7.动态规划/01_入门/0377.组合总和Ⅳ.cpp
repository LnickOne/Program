/*
给你一个由 不同 整数组成的数组 nums ，和一个目标整数 target 。
请你从 nums 中找出并返回总和为 target 的元素组合的个数。
示例 1：
输入：nums = [1,2,3], target = 4
输出：7
解释：
所有可能的组合为：
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
请注意，顺序不同的序列被视作不同的组合。

示例 2：
输入：nums = [9], target = 3
输出：0
*/
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
    int combinationSum4(vector<int> &nums, int target)
    {
        // 记忆化搜索法
        vector<int> memory(target + 1, -1);
        // 初始化
        memory[0] = 1;
        // 递推公式 memory[i]=memory[i-1]+memory[i-2]+...+memory[i-nums.size()]
        int result = dfs(nums, target, memory);
        return result;
    }
    int dfs(vector<int> &nums, int target, vector<int> &memory)
    {
        if (target == 0)
            return 1; // 爬到底
        int &result = memory[target];
        if (result != -1)
            return result; // 记忆化
        result = 0;
        for (int x : nums)
            if (x <= target)
                result += dfs(nums, target - x, memory);
        return result;
    }
    //完全背包法
    int combinationSum(vector<int> &nums, int target)
    {
        // 题目说是组合，但其实是不同的排列（因为可以重复选择元素）
        int backpack_capacity = target;
        vector<unsigned long> dp(backpack_capacity + 1, 0); // 改为使用 unsigned long 类型
        dp[0] = 1;
        for (int j = 0; j <= backpack_capacity; j += 1) // 遍历背包，如果先遍历背包，就要从0开始
        {
            for (int i = 0; i < nums.size(); i += 1) // 遍历物品
            {
                if (j - nums[i] >= 0)
                {
                    dp[j] = dp[j] + dp[j - nums[i]];
                }
            }
        }
        return dp[target];
    }
};

int main()
{
    Solution s;
    vector<int> nums = {1, 2, 3};
    int target = 4;
    cout << s.combinationSum4(nums, target) << endl;
    return 0;
}