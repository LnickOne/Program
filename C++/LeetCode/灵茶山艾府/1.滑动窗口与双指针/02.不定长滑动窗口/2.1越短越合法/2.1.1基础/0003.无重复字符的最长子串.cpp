/*
给定一个字符串，请你找出其中不含有重复字符的最长子串的长度。
示例1:
输入: "abcabcbb"
输出: 3
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:
输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:
输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是"wke"，所以其长度为 3。
请注意，你的答案必须是子串的长度，"pwke"是一个子序列，不是子串。
*/
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
class Solution
{
public:
  int lengthOfLongestSubstring(string s)
  {
    int result = 0;
    unordered_map<char, int> chMap;
    int left = 0;
    for (int right = 0; right < s.size(); right += 1)
    {
      chMap[s[right]] += 1;
      while (chMap[s[right]] > 1)
      {
        chMap[s[left]] -= 1;
        left += 1;
      }
      result = max(result, right - left + 1);
    }
    return result;
  }
};

int main()
{
  Solution s;
  string s_1 = "abcabcbb";
  string s_2 = "bbbbb";
  string s_3 = "pwwkew";
  string s_4 = "au";
  cout << s.lengthOfLongestSubstring(s_1) << endl;
  cout << s.lengthOfLongestSubstring(s_2) << endl;
  cout << s.lengthOfLongestSubstring(s_3) << endl;
  cout << s.lengthOfLongestSubstring(s_4) << endl;
  return 0;
}