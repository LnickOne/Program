#include <iostream>  // 添加输入输出流头文件
#include <climits>   // 已包含，用于INT_MIN/INT_MAX
using namespace std; // 添加命名空间声明

class Solution
{
public:
    int divide(int dividend, int divisor)
    {
        // 处理特殊情况：防止溢出
        if (dividend == INT_MIN && divisor == -1)
        {
            return INT_MAX;
        }

        // 确定结果的符号
        bool neg = (dividend < 0) ^ (divisor < 0);

        // 使用long long避免溢出
        long long dvd = llabs((long long)dividend);
        long long dvs = llabs((long long)divisor);

        int res = 0;

        // 注意循环条件是大于等于, 因为等于情况下仍有商, 为1
        while (dvd >= dvs)
        {
            // 2的幂初始化为1
            long long mi = 1;
            // 除数乘积初始化为除数
            long long cur = dvs;

            // 注意循环条件是大于等于, 相等时表示恰好整除
            while (dvd >= (cur << 1))
            {
                // 2的幂和除数乘积不断左移一位, 直到最接近且小于等于被除数
                cur <<= 1;
                mi <<= 1;
            }

            // 商加上当前的2的幂
            res += mi;
            // 被除数减去已经使用的除数乘积
            dvd -= cur;
        }

        // 恢复符号
        return neg ? -res : res;
    }
};
int main()
{
    Solution s;
    int dividend = 15;
    int divisor = 2;
    int result = s.divide(dividend, divisor);
    cout << "Result: " << result << endl; // 修复转义字符 &quot; 为 "
    return 0;
}