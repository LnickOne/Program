# @lc app=leetcode.cn id=3 lang=python3
# [3] 无重复字符的最长子串
# https://leetcode.cn/problems/longest-substring-without-repeating-characters/description/
# algorithms
# Medium (41.80%)
# Likes:    11173
# Dislikes: 0
# Total Accepted:    3.9M
# Total Submissions: 9.2M
# Testcase Example:  '"abcabcbb"'
# 给定一个字符串 s ，请你找出其中不含有重复字符的 最长 子串 的长度。
# 示例 1:
# 输入: s = "abcabcbb"
# 输出: 3
# 解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。注意 "bca" 和 "cab" 也是正确答案。
# 示例 2:
# 输入: s = "bbbbb"
# 输出: 1
# 解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
# 示例 3:
# 输入: s = "pwwkew"
# 输出: 3
# 解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
# 请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
# 提示：
# 0 <= s.length <= 5 * 10^4
# s 由英文字母、数字、符号和空格组成
# @lc code=start
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        if not s:
            return 0
        chMap = {}
        left = 0
        result = 0
        for right in range(len(s)):
            chMap[s[right]] = chMap.get(s[right], 0) + 1
            while chMap[s[right]] > 1:
                chMap[s[left]] = chMap.get(s[left], 0) - 1
                if chMap[s[left]] == 0:
                    del chMap[s[left]]
                left += 1
            result = max(result, right - left + 1)
        return result


print(Solution().lengthOfLongestSubstring("abcabcbb"))  # Output: 3
print(Solution().lengthOfLongestSubstring("bbbbb"))  # Output: 1
print(Solution().lengthOfLongestSubstring("pwwkew"))  # Output: 3
print(Solution().lengthOfLongestSubstring(""))  # Output: 0

# @lc code=end
