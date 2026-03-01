/*
给你一个字符串 S，找出所有长度为 K 且不含重复字符的子串，请你返回全部满足要求的子串的 数目。
示例 1：
输入：S = "havefunonleetcode", K = 5
输出：6
解释：
这里有 6 个满足题意的子串，分别是：'havef','avefu','vefun','efuno','etcod','tcode'。
示例 2：
输入：S = "home", K = 5
输出：0
解释：
注意：K 可能会大于 S 的长度。在这种情况下，就无法找到任何长度为 K 的子串。
*/
#include <iostream>
#include <unordered_map>
using namespace std;
class Solution
{
public:
  int numKLenSubstrNoRepeats(string s, int k)
  {
    if (k > s.size())
      return 0;
    int result = 0;
    unordered_map<char, int> chMap;
    // 处理第一个窗口
    for (int i = 0; i < k; i += 1)
    {
      chMap[s[i]] += 1;
    }
    if (chMap.size() == k)
    {
      result += 1;
    }
    // 处理后续窗口
    for (int i = k; i < s.size(); i += 1)
    {
      chMap[s[i]] += 1;
      chMap[s[i - k]] -= 1;
      if (chMap[s[i - k]] == 0)
        chMap.erase(s[i - k]);
      if (chMap.size() == k)
        result += 1;
    }
    return result;
  }
};

int main()
{
  Solution s;
  string s1 = "havefunonleetcode";
  string s2 = "home";
  string s3 = "aabab";
  cout << s.numKLenSubstrNoRepeats(s1, 5) << endl;
  cout << s.numKLenSubstrNoRepeats(s2, 5) << endl;
  cout << s.numKLenSubstrNoRepeats(s3, 2) << endl;
  return 0;
}
