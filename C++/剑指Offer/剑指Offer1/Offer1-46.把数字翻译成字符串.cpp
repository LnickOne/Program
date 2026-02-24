#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/*
现有一串神秘的密文 ciphertext，经调查，密文的特点和规则如下：
密文由非负整数组成
数字 0-25 分别对应字母 a-z
请根据上述规则将密文 ciphertext 解密为字母，并返回共有多少种解密结果。
示例 1:
输入: ciphertext = 216612
输出: 6
解释: 216612 解密后有 6 种不同的形式，分别是 "cbggbc"，"vggbc"，"vggm"，"cbggm"，"cqgbc" 和 "cqgm"
*/
class Solution
{
public:
    /*
    动态规划五部曲
    1. 确定dp数组以及下标的含义
    2. 确定递推关系
    3. 确定初始值
    4. 确定遍历顺序
    5. 举例推导dp数组
    */
    int translateNum(int num)
    {
        string s = to_string(num);
        int len = s.size();
        vector<int> dp(len + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= len; i++)
        {
            int pre = stoi(s.substr(i - 2, 2));
            if (pre >= 10 && pre <= 25)
            {
                dp[i] = dp[i - 1] + dp[i - 2];
            }
            else
            {
                dp[i] = dp[i - 1];
            }
        }
        return dp[len];
    }
};

int main()
{
    cout << Solution().translateNum(216612) << endl;
    return 0;
}