/*
给你一个字符串 s
，请找出满足每个字符最多出现两次的最长子字符串，并返回该子字符串的 最大 长度。
示例 1：
输入： s = "bcbbbcba"
输出： 4
解释：
以下子字符串长度为 4，并且每个字符最多出现两次："bcbbbcba"。

示例 2：
输入： s = "aaaa"
输出： 2
解释：
以下子字符串长度为 2，并且每个字符最多出现两次："aaaa"。
*/
#include <iostream>
#include <unordered_map>
using namespace std;
class Solution
{
public:
  int maximumLengthSubstring(string s)
  {
    int result = 0;
    int left = 0;
    unordered_map<char, int> chMap;
    for (int right = 0; right < s.size(); right += 1)
    {
      chMap[s[right]] += 1;
      if (chMap[s[right]] > 2)
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
  string str = "bcbbbcba";
  cout << s.maximumLengthSubstring(str) << endl;
  str = "aaaa";
  cout << s.maximumLengthSubstring(str) << endl;
  str = "abcdefghijklmnopqrstuvwxyz";
  cout << s.maximumLengthSubstring(str) << endl;
  str = "aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz";
  cout << s.maximumLengthSubstring(str) << endl;
  return 0;
}