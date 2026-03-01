/*
给你两个长度相同的字符串，s 和 t。
将 s 中的第 i 个字符变到 t 中的第 i 个字符需要|s[i]-t[i]|的开销（开销可能为0），也就是两个字符的 ASCII 码值的差的绝对值。
用于变更字符串的最大预算是maxCost。
在转化字符串时，总开销应当小于等于该预算，这也意味着字符串的转化可能是不完全的。
如果可以将 s 的子字符串转化为它在t中对应的子字符串，则返回可以转化的最大长度。
如果 s 中没有子字符串可以转化成 t中对应的子字符串，则返回 0。

示例 1：
输入：s = "abcd", t = "bcdf", maxCost = 3
输出：3
解释：s 中的 "abc" 可以变为 "bcd"。开销为 3，所以最大长度为 3。

示例 2：
输入：s = "abcd", t = "cdef", maxCost = 3
输出：1
解释：s 中的任一字符要想变成 t 中对应的字符，其开销都是 2。因此，最大长度为 1。

示例 3：
输入：s = "abcd", t = "acde", maxCost = 0
输出：1
解释：a -> a, cost = 0，字符串未发生变化，所以最大长度为 1。
*/
#include <iostream>
#include <unordered_map>
using namespace std;
class Solution
{
public:
  int equalSubstring(string s, string t, int maxCost)
  {
    int result = 0;
    int left = 0;
    int totalCost = 0;
    for (int right = 0; right < t.size(); right += 1)
    {
      totalCost += abs(t[right] - s[right]);
      while (totalCost > maxCost && left <= right) // 当总成本超过maxCost时，移动左指针并调整成本
      {
        totalCost -= abs(t[left] - s[left]);
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
  string s1 = "abcd";
  string t1 = "bcdf";
  int maxCost1 = 3;
  int result1 = s.equalSubstring(s1, t1, maxCost1);
  cout << result1 << endl;
  string s2 = "abcd";
  string t2 = "cdef";
  int maxCost2 = 3;
  int result2 = s.equalSubstring(s2, t2, maxCost2);
  cout << result2 << endl;
  return 0;
}