/*
给你一个整数数组 cost ，其中 cost[i] 是从楼梯第 i 个台阶向上爬需要支付的费用。一旦你支付此费用，即可选择向上爬一个或者两个台阶。
你可以选择从下标为 0 或下标为 1 的台阶开始爬楼梯。
请你计算并返回达到楼梯顶部的最低花费。
示例 1：
输入：cost = [10,15,20]
输出：15
解释：你将从下标为 1 的台阶开始。
- 支付 15 ，向上爬两个台阶，到达楼梯顶部。
总花费为 15 。
示例 2：
输入：cost = [1,100,1,1,1,100,1,1,100,1]
输出：6
解释：你将从下标为 0 的台阶开始。
- 支付 1 ，向上爬两个台阶，到达下标为 2 的台阶。
- 支付 1 ，向上爬两个台阶，到达下标为 4 的台阶。
- 支付 1 ，向上爬两个台阶，到达下标为 6 的台阶。
- 支付 1 ，向上爬一个台阶，到达下标为 7 的台阶。
- 支付 1 ，向上爬两个台阶，到达下标为 9 的台阶。
- 支付 1 ，向上爬一个台阶，到达楼梯顶部。
总花费为 6 。
*/
#include <vector>
#include <iostream>
using namespace std;
class Solution
{
public:
    /*
    1. 确定dp数组以及下标的含义
    dp[i]：表示从下标为0或下标为1的台阶开始爬楼梯到达楼梯i的位置的最小花费值
    2. 确定递推关系
    通过本题可以得知，一步可以跳一个台阶或者两个台阶，
    所以dp[i]由dp[i-1]跳了一步花费cost[i-1]得到或者dp[i-2]跳了两步花费cost[i-2]得到,
    并且求最小花费，所以再加一个min
    则递推关系为dp[i] = min(dp[i-1]+cost[i-1] + dp[i-2]+cost[i-2])
    3. 确定初始值
    可以选择从下标为 0 或下标为 1 的台阶开始爬楼梯，所以初始化为0(不需要任何费用)，之后再向上跳的时候才有花费
    dp[0] = 0;
    dp[1] = 0;
    */
    int minCostClimbingStairs(vector<int> &cost)
    {
        // 递推法
        vector<int> dp(cost.size() + 1);
        dp[0] = 0;
        dp[1] = 0;
        for (int i = 2; i <= cost.size(); i += 1)
        {
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]); // 从下标为0或下标为1的台阶开始爬楼梯到达楼梯i的位置的最小花费值
        }
        return dp[cost.size()];
    }
    int minCostClimbingStairs_memory(vector<int> &cost)
    {
        // 记忆化搜索法
        int result = 0;
        int n = cost.size();
        vector<int> memory(n, -1); // 只需要cost数组大小
        // 可以从第0步或第1步开始
        result = min(dfs(n - 1, cost, memory), dfs(n - 2, cost, memory));
        return result;
    }

    int dfs(int i, vector<int> &cost, vector<int> &memory)
    {
        // 基础情况：已经到达或越过顶部
        if (i < 0)
            return 0; // 越界返回0
        if (i == 0)
            return cost[0]; // 第一步的花费
        if (i == 1)
            return cost[1]; // 第二步的花费
        // 检查记忆化
        if (memory[i] != -1)
            return memory[i];
        // 关键：只能选择爬1步或爬2步，不是同时！
        int climb_one = dfs(i - 1, cost, memory) + cost[i]; // 爬1步
        int climb_two = dfs(i - 2, cost, memory) + cost[i]; // 爬2步
        memory[i] = min(climb_one, climb_two);
        return memory[i];
    }
};

int main()
{
    vector<int> cost = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    Solution sol;
    cout << sol.minCostClimbingStairs_memory(cost) << endl;
}