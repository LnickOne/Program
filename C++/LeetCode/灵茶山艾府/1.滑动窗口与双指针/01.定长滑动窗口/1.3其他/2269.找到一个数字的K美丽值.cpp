/*
一个整数 num 的 k 美丽值定义为 num 中符合以下条件的 子字符串 数目：
-子字符串长度为 k 。
-子字符串能整除 num 。
-给你整数 num 和 k ，请你返回 num 的 k 美丽值。
注意：
允许有 前缀 0 。0 不能整除任何值。
一个 子字符串 是一个字符串里的连续一段字符序列。
示例 1：
输入：num = 240, k = 2
输出：2
解释：以下是 num 里长度为 k 的子字符串：
- "240" 中的 "24" ：24 能整除 240 。
- "240" 中的 "40" ：40 能整除 240 。
所以，k 美丽值为 2 。
示例 2：
输入：num = 430043, k = 2
输出：2
解释：以下是 num 里长度为 k 的子字符串：
- "430043" 中的 "43" ：43 能整除 430043 。
- "430043" 中的 "30" ：30 不能整除 430043 。
- "430043" 中的 "00" ：0 不能整除 430043 。
- "430043" 中的 "04" ：4 不能整除 430043 。
- "430043" 中的 "43" ：43 能整除 430043 。
所以，k 美丽值为 2 。
*/
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
    int divisorSubstrings(int num, int k)
    {
        int result = 0;
        string numStr = to_string(num);
        // string nums;
        // // 处理第一个窗口
        // for (int i = 0; i < k; i += 1)
        // {
        //     nums += numStr[i];
        // }
        // if (stoi(nums) != 0 && num % (stoi(nums)) == 0)
        // {
        //     result += 1;
        // }
        // // 处理后续窗口
        // for (int i = k; i < numStr.size(); i += 1)
        // {
        //     nums += numStr[i]; // 添加下一个字符
        //     nums.erase(0, 1);  // 移除前一个字符
        //     if (stoi(nums) != 0 && num % stoi(nums) == 0)
        //     {
        //         result += 1;
        //     }
        // }
        // 处理第一个窗口：构建初始数字
        int subNum = 0;
        for (int i = 0; i < k; i += 1)
        {
            subNum = subNum * 10 + (numStr[i] - '0');
        }
        if (subNum != 0 && num % subNum == 0)
        {
            result += 1;
        }
        // 处理后续窗口：滑动窗口计算
        int power = 1;
        for (int i = 1; i < k; i += 1) // 计算 10^(k-1)
        {
            power *= 10;
        }
        for (int i = k; i < numStr.size(); i += 1)
        {
            // 移除最左边的数字，添加新数字
            subNum = (subNum % power) * 10 + (numStr[i] - '0');
            if (subNum != 0 && num % subNum == 0)
            {
                result += 1;
            }
        }
        return result;
    }
};
int main()
{
    int num = 430043;
    int k = 2;
    Solution s;
    int result = s.divisorSubstrings(num, k);
    cout << result << endl;
    return 0;
}