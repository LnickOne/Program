/*
给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词的子串，返回这些子串的起始索引。不考虑答案输出的顺序。
异位词指由相同字母重排列形成的字符串（包括相同的字符串）。

示例 1:
输入: s = "cbaebabacd", p = "abc"
输出: [0,6]
解释:
起始索引等于 0 的子串是 "cba", 它是 "abc" 的异位词。
起始索引等于 6 的子串是 "bac", 它是 "abc" 的异位词。

示例 2:
输入: s = "abab", p = "ab"
输出: [0,1,2]
解释:
起始索引等于 0 的子串是 "ab", 它是 "ab" 的异位词。
起始索引等于 1 的子串是 "ba", 它是 "ab" 的异位词。
起始索引等于 2 的子串是 "ab", 它是 "ab" 的异位词。
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
class Solution
{
public:
  vector<int> findAnagrams(string s, string p)
  {
    if (p.size() > s.size())
    {
      return {};
    }
    vector<int> result;
    int k = p.size();
    unordered_map<char, int> s_map;
    unordered_map<char, int> p_map;
    // 处理第一个窗口
    for (int i = 0; i < k; i += 1)
    {
      s_map[s[i]] += 1;
      p_map[p[i]] += 1;
    }
    if (s_map == p_map) // 检查第一个窗口是否符合
    {
      result.push_back(0);
    }
    // 处理后续窗口
    for (int i = k; i < s.size(); i += 1)
    {
      s_map[s[i]] += 1;     // 添加窗口右侧新字符
      s_map[s[i - k]] -= 1; // 移除窗口左侧字符
      if (s_map[s[i - k]] == 0)
      {
        s_map.erase(s[i - k]);
      }
      // 比较当前窗口与p的字符频率
      if (s_map == p_map)
      {
        result.push_back(i - k + 1); // 添加正确的起始索引
      }
    }
    return result;
  }
};

int main()
{
  string s = "cbaebabacd";
  string p = "abc";
  string s1 = "eklpyqrbgjdwtcaxzsnifvhmoueklpyqrbgjdwtcaxzsnifvhmoueklpyqrbg";
  string p1 = "yqrbgjdwtcaxzsnifvhmou";
  Solution sol;
  vector<int> result = sol.findAnagrams(s, p);
  for (int i = 0; i < result.size(); i++)
  {
    cout << result[i] << " ";
  }
  cout << endl;
  vector<int> result1 = sol.findAnagrams(s1, p1);
  for (int i = 0; i < result1.size(); i++)
  {
    cout << result1[i] << " ";
  }
  cout << endl;
  return 0;
}
