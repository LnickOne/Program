#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
    /*
    动态规划五部曲
    1. 确定dp数组以及下标的含义
    dp[i]：表示[0,i-1]最大和的连续子数组
    2. 确定递推关系
    dp[i] = max(dp[i - 1] + sales[i], sales[i])
    3. 确定初始值
    dp[0] = sales[0]
    4. 确定遍历顺序
    5. 举例推导dp数组
    */
    int maxSales(vector<int> &sales)
    {
        vector<int> dp(sales.size(), 0);
        dp[0] = sales[0];
        for (int i = 1; i < sales.size(); i++)
        {
            dp[i] = max(dp[i - 1] + sales[i], sales[i]);
        }
        return *max_element(dp.begin(), dp.end());
    }
};

int main()
{
    vector<int> sales = {1, -2, 3, 5, -2, 6, -1};
    Solution s;
    cout << s.maxSales(sales) << endl;
    return 0;
}