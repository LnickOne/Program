/*
给你字符串 s 和整数 k 。

请返回字符串 s 中长度为 k 的单个子字符串中可能包含的最大元音字母数。

英文中的 元音字母 为（a, e, i, o, u）。
示例 1：
输入：s = "abciiidef", k = 3
输出：3
解释：子字符串 "iii" 包含 3 个元音字母。

示例 2：
输入：s = "aeiou", k = 2
输出：2
解释：任意长度为 2 的子字符串都包含 2 个元音字母。

示例 3：
输入：s = "leetcode", k = 3
输出：2
解释："lee"、"eet" 和 "ode" 都包含 2 个元音字母。

示例 4：
输入：s = "rhythms", k = 4
输出：0
解释：字符串 s 中不含任何元音字母。

示例 5：
输入：s = "tryhard", k = 4
输出：1
*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
class Solution
{
public:
    int maxVowels(string s, int k)
    {
        if (s.empty() || k == 0)
            return 0;
        int result = 0;
        int count = 0;
        unordered_map<char, int> chMap{
            {'a', 1},
            {'e', 1},
            {'i', 1},
            {'o', 1},
            {'u', 1},
        };
        for (int i = 0; i < k; i += 1)
        {
            if (chMap.find(s[i]) != chMap.end()) // 计算第一个窗口的元音字母的总数
            {
                count++;
            }
        }
        result = max(result, count);
        for (int i = k; i < s.size(); ++i)
        {
            if (chMap.find(s[i]) != chMap.end()) // 如果窗口移动后新进入的元素是元音字母，则总数 + 1
            {
                count += 1;
            }
            if (chMap.find(s[i - k]) != chMap.end()) // 如果窗口移动后移出的元素是元音字母，则总数 - 1
            {
                count -= 1;
            }
            result = max(result, count);
        }
        return result;
    }
};
int main()
{
    string s1 = "abciiidef";
    int k1 = 3;
    string s2 = "aeiou";
    int k2 = 2;
    string s3 = "leetcode";
    int k3 = 3;
    string s4 = "rhythms";
    int k4 = 4;
    string s5 = "tryhard";
    int k5 = 4;
    Solution s;
    cout << s.maxVowels(s1, k1) << endl;
    cout << s.maxVowels(s2, k2) << endl;
    cout << s.maxVowels(s3, k3) << endl;
    cout << s.maxVowels(s4, k4) << endl;
    cout << s.maxVowels(s5, k5) << endl;
    return 0;
}