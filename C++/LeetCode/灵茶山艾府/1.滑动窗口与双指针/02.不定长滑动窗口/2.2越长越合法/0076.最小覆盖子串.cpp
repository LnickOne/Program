/*
给你一个字符串 s 、一个字符串 t 。
返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t所有字符的子串，则返回空字符串 "" 。
注意：对于 t中重复字符，我们寻找的子字符串中该字符数量必须不少于 t 中该字符数量。
如果 s 中存在这样的子串，我们保证它是唯一的答案。
示例 1：
输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"
解释：最小覆盖子串 "BANC" 包含来自字符串 t 的 'A'、'B' 和 'C'。
示例 2：
输入：s = "a", t = "a"
输出："a"
解释：整个字符串 s 是最小覆盖子串。
示例 3:
输入: s = "a", t = "aa"
输出: ""
解释: t 中两个字符 'a' 均应包含在 s 的子串中，
因此没有符合条件的子字符串，返回空字符串。
 */
#include <algorithm>
#include <climits>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
class Solution
{
public:
  string minWindow(string s, string t)
  {
    if (t.size() > s.size())
    {
      return "";
    }
    string result = "";
    unordered_map<char, int> t_map;
    unordered_map<char, int> match_map;
    for (char &ch : t)
    {
      t_map[ch] += 1;
    }
    int length = INT_MAX;
    int valid = 0; // 记录已完全匹配的字符种类数
    int begin = 0; // 记录最小窗口的起始位置
    int left = 0;
    for (int right = 0; right < s.size(); right += 1)
    {
      if (t_map.find(s[right]) != t_map.end())
      {
        match_map[s[right]] += 1;
        if (match_map[s[right]] == t_map[s[right]]) // 当窗口中该字符数量等于t中数量时，增加有效计数
        {
          valid += 1;
        }
      }
      while (valid == t_map.size()) // 当所有字符都匹配时有效计数即为t_map的size，收缩左边界
      {
        // 这是一个有效的覆盖子串，首先计算当前窗口长度，并更新最小窗口信息
        if (right - left + 1 < length)
        {
          length = right - left + 1;
          begin = left; // 记录最小窗口的起始位置
          result = s.substr(begin, length);
        }
        if (t_map.find(s[left]) != t_map.end()) // 然后再移动左边界，如果左边界的字符包含在t内，则有效计数-1
        {
          if (match_map[s[left]] == t_map[s[left]])
          {
            valid -= 1; // 如果移除后数量不满足at中的要求，减少有效计数
          }
          match_map[s[left]] -= 1;
        }
        left += 1;
      }
    }
    if (length != INT_MAX)
    {
      result = s.substr(begin, length);
    }
    return result;
  }
};
int main()
{
  string s_1 = "ADOBECODEBANC", t_1 = "ABC";
  string s_2 = "a", t_2 = "a";
  string s_3 = "a", t_3 = "aa";
  Solution sol;
  string res_1 = sol.minWindow(s_1, t_1);
  string res_2 = sol.minWindow(s_2, t_2);
  string res_3 = sol.minWindow(s_3, t_3);
  cout << res_1 << endl;
  cout << res_2 << endl;
  cout << res_3 << endl;
  return 0;
}