/*
你有一个炸弹需要拆除，给你一个长度为 n 的 循环 数组 code 以及一个密钥 k 。
为了获得正确的密码，你需要替换掉每一个数字。所有数字会 同时 被替换。
如果 k > 0 ，将第 i 个数字用 接下来 k 个数字之和替换。
如果 k < 0 ，将第 i 个数字用 之前 k 个数字之和替换。
如果 k == 0 ，将第 i 个数字用 0 替换。
由于 code 是循环的， code[n-1] 下一个元素是 code[0] ，且 code[0] 前一个元素是 code[n-1] 。
给你 循环 数组 code 和整数密钥 k ，请你返回解密后的结果来拆除炸弹！

示例 1：
输入：code = [5,7,1,4], k = 3
输出：[12,10,16,13]
解释：每个数字都被接下来 3 个数字之和替换。解密后的密码为 [7+1+4, 1+4+5, 4+5+7, 5+7+1]。注意到数组是循环连接的。

示例 2：
输入：code = [1,2,3,4], k = 0
输出：[0,0,0,0]
解释：当 k 为 0 时，所有数字都被 0 替换。

示例 3：
输入：code = [2,4,9,3], k = -2
输出：[12,5,6,13]
解释：解密后的密码为 [3+9, 2+3, 4+2, 9+4] 。注意到数组是循环连接的。如果 k 是负数，那么和为 之前 的数字。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
    vector<int> decrypt(vector<int> &code, int k)
    {
        vector<int> result;
        if (k == 0)
        {
            result.assign(code.size(), 0);
            return result;
        }
        else if (k > 0)
        {
            for (int i = 0; i < k; i += 1)
            {
                code.push_back(code[i]);
            }
            int total = 0;
            // 处理第一个窗口
            for (int i = 0; i < k; i += 1)
            {
                total += code[i + 1];
            }
            result.push_back(total);
            // 处理后续窗口
            for (int i = k; i < code.size() - 1; i += 1)
            {
                total += code[i + 1];
                total -= code[i + 1 - k];
                result.push_back(total);
            }
        }
        else if (k < 0)
        {
            int k_ = abs(k);
            vector<int> elementInsert;
            // 先保存需要插入的元素（原数组的最后k_个元素）
            for (int i = 0; i < k_; i += 1)
            {
                elementInsert.push_back(code[code.size() - k_ + i]);
            }
            reverse(elementInsert.begin(), elementInsert.end());
            for (int i = 0; i < k_; i += 1)
            {
                code.insert(code.begin(), elementInsert[i]);
            }
            int total = 0;
            // 处理第一个窗口
            for (int i = 0; i < k_; i += 1)
            {
                total += code[i];
            }
            result.push_back(total);
            // 处理后续窗口
            for (int i = k_; i < code.size() - 1; i += 1)
            {
                total += code[i];
                total -= code[i - k_];
                result.push_back(total);
            }
        }
        return result;
    }
};
int main()
{
    Solution sol;
    vector<int> code1 = {5, 7, 1, 4};
    int k1 = 3;
    vector<int> res1 = sol.decrypt(code1, k1);
    for (int num : res1)
        cout << num << " ";
    cout << endl;
    vector<int> code2 = {1, 2, 3, 4};
    int k2 = 0;
    vector<int> res2 = sol.decrypt(code2, k2);
    for (int num : res2)
        cout << num << " ";
    cout << endl;
    vector<int> code3 = {2, 4, 9, 3};
    int k3 = -2;
    vector<int> res3 = sol.decrypt(code3, k3);
    for (int num : res3)
        cout << num << " ";
    cout << endl;
    return 0;
}