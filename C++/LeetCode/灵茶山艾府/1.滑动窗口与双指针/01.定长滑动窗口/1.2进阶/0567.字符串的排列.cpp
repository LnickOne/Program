/*
给你两个字符串 s1 和 s2 ，写一个函数来判断 s2 是否包含 s1 的 排列。
如果是，返回 true ；否则，返回 false 。
换句话说，s1 的排列之一是 s2 的 子串 。

示例 1：
输入：s1 = "ab" s2 = "eidbaooo"
输出：true
解释：s2 包含 s1 的排列之一 ("ba").

示例 2：
输入：s1= "ab" s2 = "eidboaoo"
输出：false
*/
#include <iostream>
#include <unordered_map>
using namespace std;
class Solution
{
public:
    bool checkInclusion(string s1, string s2)
    {
        if (s1.size() > s2.size())
            return false;
        int k = s1.size();
        unordered_map<char, int> s1Map;
        unordered_map<char, int> s2Map;
        for (const char &ch : s1)
        {
            s1Map[ch] += 1;
        }
        // 处理第一个窗口
        for (int i = 0; i < k; i += 1)
        {
            s2Map[s2[i]] += 1;
        }
        if (s1Map == s2Map)
        {
            return true;
        }
        // 处理后续窗口
        for (int i = k; i < s2.size(); i += 1)
        {
            s2Map[s2[i]] += 1;
            s2Map[s2[i - k]] -= 1;
            if (s2Map[s2[i - k]] == 0)
            {
                s2Map.erase(s2[i - k]);
            }
            if (s1Map == s2Map)
                return true;
        }
        return false;
    }
};
int main()
{
    Solution s;
    string s1 = "ab";
    string s2 = "eidbaooo";
    cout << s.checkInclusion(s1, s2) << endl;
    s1 = "ab";
    s2 = "eidboaoo";
    cout << s.checkInclusion(s1, s2) << endl;
    return 0;
}