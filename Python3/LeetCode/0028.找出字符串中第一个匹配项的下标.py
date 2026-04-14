# @lc app=leetcode.cn id=28 lang=python3
# [28] 找出字符串中第一个匹配项的下标
# https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/description/
# algorithms
# Easy (45.31%)
# Likes:    2551
# Dislikes: 0
# Total Accepted:    1.4M
# Total Submissions: 3.1M
# Testcase Example:  '"sadbutsad"\n"sad"'
# 给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串的第一个匹配项的下标（下标从 0
# 开始）。如果 needle 不是 haystack 的一部分，则返回  -1 。
# 示例 1：
# 输入：haystack = "sadbutsad", needle = "sad"
# 输出：0
# 解释："sad" 在下标 0 和 6 处匹配。
# 第一个匹配项的下标是 0 ，所以返回 0 。
# 示例 2：
# 输入：haystack = "leetcode", needle = "leeto"
# 输出：-1
# 解释："leeto" 没有在 "leetcode" 中出现，所以返回 -1 。
# 提示：
# 1 <= haystack.length, needle.length <= 10^4
# haystack 和 needle 仅由小写英文字符组成
# @lc code=start
class Solution:
    def strStr(self, haystack: str, needle: str) -> int:
        n = len(haystack)
        m = len(needle)
        
        # 特殊情况处理
        if m == 0:
            return 0
        if m > n:
            return -1
        
        # 计算前缀函数（pi 数组）
        pi = [0] * m
        for i in range(1, m):
            j = pi[i - 1]
            while j > 0 and needle[i] != needle[j]:
                j = pi[j - 1]
            if needle[i] == needle[j]:
                j += 1
            pi[i] = j
        
        # KMP 搜索
        j = 0
        for i in range(n):
            # 回退 j 直到找到匹配的前缀或 j 为 0
            while j > 0 and haystack[i] != needle[j]:
                j = pi[j - 1]
            # 如果当前字符匹配，j 前进
            if haystack[i] == needle[j]:
                j += 1
            # 如果完全匹配，返回起始位置
            if j == m:
                return i - m + 1
        
        # 未找到匹配
        return -1
print(Solution().strStr("sadbutsad", "sad"))
print(Solution().strStr("leetcode", "leeto"))
print(Solution().strStr("sq", "aksqsqsak"))

# @lc code=end
