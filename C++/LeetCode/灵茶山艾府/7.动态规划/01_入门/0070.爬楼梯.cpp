/*
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
示例 1：
输入：n = 2
输出：2
解释：有两种方法可以爬到楼顶。
1. 1 阶 + 1 阶
2. 2 阶
示例 2：
输入：n = 3
输出：3
解释：有三种方法可以爬到楼顶。
1. 1 阶 + 1 阶 + 1 阶
2. 1 阶 + 2 阶
3. 2 阶 + 1 阶
*/
#include <vector>
#include <iostream>
using namespace std;
class Solution
{
public:
    int climbStairs(int n)
    {
        // 递推法
        // dp[i]表示：从起始0阶或者起始1阶爬到第i阶,有dp[i]种方法。
        vector<int> dp(n + 1, 0);
        // 初始化
        dp[0] = 1;
        dp[1] = 1;
        // 递推关系
        for (int i = 2; i <= n; i += 1)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }

    int climbStairs_memory(int n)
    {
        // 记忆化搜索法
        int result = 0;
        vector<int> memory(n + 1, -1);
        result = dfs(n, memory);
        return result;
    }
    int dfs(int i, vector<int> &memory)
    {
        if (i <= 1)
        {
            return 1;
        }
        else if (memory[i] != -1)
        {
            return memory[i];
        }
        else if (memory[i] == -1)
        {
            memory[i] = dfs(i - 1, memory) + dfs(i - 2, memory);
        }
        return memory[i];
    }
};
int main()
{
    Solution s;
    cout << s.climbStairs(5) << endl;
    cout << s.climbStairs(6) << endl;
    cout << s.climbStairs(7) << endl;
}