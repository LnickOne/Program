/*
给你两个整数数组 prices 和 strategy，其中：
prices[i] 表示第 i 天某股票的价格。
strategy[i] 表示第 i 天的交易策略，其中：
-1 表示买入一单位股票。
0 表示持有股票。
1 表示卖出一单位股票。
同时给你一个 偶数 整数 k，你可以对 strategy 进行 最多一次 修改。一次修改包括：
选择 strategy 中恰好 k 个 连续 元素。
将前 k / 2 个元素设为 0（持有）。
将后 k / 2 个元素设为 1（卖出）。
利润 定义为所有天数中 strategy[i] * prices[i] 的 总和 。
返回你可以获得的 最大 可能利润。

注意： 没有预算或股票持有数量的限制，因此所有买入和卖出操作均可行，无需考虑过去的操作。

示例 1：
输入： prices = [4,2,8], strategy = [-1,0,1], k = 2
输出： 10
解释：
修改	策略	利润计算	利润
原始	[-1, 0, 1]	(-1 × 4) + (0 × 2) + (1 × 8) = -4 + 0 + 8	4
修改 [0, 1]	[0, 1, 1]	(0 × 4) + (1 × 2) + (1 × 8) = 0 + 2 + 8	10
修改 [1, 2]	[-1, 0, 1]	(-1 × 4) + (0 × 2) + (1 × 8) = -4 + 0 + 8	4
因此，最大可能利润是 10，通过修改子数组 [0, 1] 实现。

示例 2：
输入： prices = [5,4,3], strategy = [1,1,0], k = 2
输出： 9
解释：
修改	策略	利润计算	利润
原始	[1, 1, 0]	(1 × 5) + (1 × 4) + (0 × 3) = 5 + 4 + 0	9
修改 [0, 1]	[0, 1, 0]	(0 × 5) + (1 × 4) + (0 × 3) = 0 + 4 + 0	4
修改 [1, 2]	[1, 0, 1]	(1 × 5) + (0 × 4) + (1 × 3) = 5 + 0 + 3	8
因此，最大可能利润是 9，无需任何修改即可达成。
*/
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
    long maxProfit(vector<int> &prices, vector<int> &strategy, int k)
    {
        long total = 0;
        long sum = 0;
        // 计算第一个窗口
        for (int i = 0; i < k / 2; i++)
        {
            total += prices[i] * strategy[i];
            sum -= prices[i] * strategy[i];
        }
        for (int i = k / 2; i < k; i++)
        {
            total += prices[i] * strategy[i];
            sum += prices[i] * (1 - strategy[i]);
        }
        long max_sum = max(sum, 0L);
        for (int i = k; i < prices.size(); i++)
        {
            int p = prices[i], s = strategy[i];
            total += p * s;
            sum += p * (1 - s) - prices[i - k / 2] + prices[i - k] * strategy[i - k];
            max_sum = max(max_sum, sum);
        }
        return total + max_sum;
    }
};
int main()
{
    vector<int> prices = {4, 2, 8};
    vector<int> strategy = {-1, 0, 1};
    int k = 2;
    Solution s;
    cout << s.maxProfit(prices, strategy, k) << endl;
    prices = {5, 4, 3};
    strategy = {1, 1, 0};
    k = 2;
    cout << s.maxProfit(prices, strategy, k) << endl;
    prices = {1, 2, 3, 4, 5, 6};
    strategy = {-1, 0, 1, -1, 0, 1};
    k = 2;
    cout << s.maxProfit(prices, strategy, k) << endl;
    prices = {1, 2, 3, 4, 5, 6};
    strategy = {1, 1, 1, 1, 1, 1};
    k = 2;
    cout << s.maxProfit(prices, strategy, k) << endl;
    return 0;
}