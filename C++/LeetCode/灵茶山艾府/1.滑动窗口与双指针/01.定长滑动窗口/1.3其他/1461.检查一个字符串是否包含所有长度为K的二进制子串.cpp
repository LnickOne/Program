/*
给你一个二进制字符串 s 和一个整数 k 。
如果所有长度为 k 的二进制字符串都是 s 的子串，请返回 true ，否则请返回 false 。

示例 1：
输入：s = "00110110", k = 2
输出：true
解释：长度为 2 的二进制串包括 "00"，"01"，"10" 和 "11"。它们分别是 s 中下标为0，1，3，2 开始的长度为 2 的子串。

示例 2：
输入：s = "0110", k = 1
输出：true
解释：长度为 1 的二进制串包括 "0" 和 "1"，显然它们都是 s 的子串。

示例 3：
输入：s = "0110", k = 2
输出：false
解释：长度为 2 的二进制串 "00" 没有出现在 s 中。
*/
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;
class Solution
{
public:
  bool hasAllCodes(string s, int k)
  {
    if (s.length() < k)
    {
      return false;
    }
    // 1.建立一个集合存储所有长度为k的二进制子串
    unordered_set<string> result;
    string path;
    backtracking(k, path, result);
    // 2.滑动窗口，检查每个长度为k的子串是否在集合中
    string sub_str = s.substr(0, k); // 处理第一个窗口
    result.erase(sub_str);           // 直接检查并删除，无需迭代器
    // 处理后续窗口
    for (int i = k; i < s.size(); i += 1)
    {
      sub_str = s.substr(i - k + 1, k);
      result.erase(sub_str); // unordered_set的erase可以直接传入值
    }
    return result.empty();
  }

  void backtracking(int k, string &path, unordered_set<string> &result)
  {
    if (path.size() == k)
    {
      result.insert(path); // 插入集合而不是vector
      return;
    }

    for (const char &ch : {'0', '1'}) // 每一层有两个选择：添加'0'或添加'1'
    {
      path.push_back(ch);            // 做选择
      backtracking(k, path, result); // 递归到下一层
      path.pop_back();               // 回溯，撤销选择
    }
  }
};
int main()
{
  Solution solution;
  string s = "00110110";
  int k = 2;
  bool result = solution.hasAllCodes(s, k);
  cout << result << endl;
  string s1 = "0110";
  int k1 = 2;
  bool result1 = solution.hasAllCodes(s1, k1);
  cout << result1 << endl;
  string s2 = "0110";
  int k2 = 1;
  bool result2 = solution.hasAllCodes(s2, k2);
  cout << result2 << endl;
  return 0;
}
