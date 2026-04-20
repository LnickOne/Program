#
# @lc app=leetcode.cn id=14 lang=python3
#
# [14] 最长公共前缀
#

# @lc code=start
from typing import List


class Solution:
    def longestCommonPrefix(self, strs: List[str]) -> str:
        if not strs:
            return ""
        result = strs[0]
        for i in range(1, len(strs)):
            result = self.commonPrefix_dp(result, strs[i])
            if not result:
                return ""
        return result

    # 暴力法
    def commonPrefix(self, str1: str, str2: str) -> str:
        if not str1 or not str2:
            return ""
        result = ""
        for i in range(min(len(str1), len(str2))):
            if str1[i] != str2[i]:
                return result
            result += str1[i]
        return result

    # 动态规划法
    def commonPrefix_dp(self, str1: str, str2: str) -> str:
        if not str1 or not str2:
            return ""
        result = ""
        # dp[i][j] 表示 str1[:i] 与 str2[:j] 的公共前缀长度（仅对角线会被使用）
        dp = [[0] * (len(str2) + 1) for _ in range(len(str1) + 1)]
        max_len = 0
        for i in range(1, min(len(str1), len(str2)) + 1):
            if str1[i - 1] == str2[i - 1]:
                dp[i][i] = dp[i - 1][i - 1] + 1
            elif str1[i - 1] != str2[i - 1]:
                break
            max_len = max(max_len, dp[i][i])
        result = str1[:max_len]
        return result

    # def commonPrefix_dp(self, str1: str, str2: str) -> str:
    #     if not str1 or not str2:
    #         return ""

    #     dp = [[0] * (len(str2) + 1) for _ in range(len(str1) + 1)]
    #     max_len = 0
    #     for i in range(1, min(len(str1), len(str2)) + 1):
    #         if str1[i - 1] == str2[i - 1]:
    #             dp[i][i] = dp[i - 1][i - 1] + 1
    #             max_len = dp[i][i]
    #         else:
    #             break
    #     return str1[:max_len]


print(Solution().longestCommonPrefix(["flower", "flow", "flight"]))  # 输出fl
print(Solution().longestCommonPrefix(["dog", "racecar", "car"]))  # 输出""
print(Solution().longestCommonPrefix([""]))  # 输出""
print(Solution().longestCommonPrefix(["a"]))  # 输出a
print(Solution().longestCommonPrefix(["ab", "a"]))  # 输出a


# @lc code=end
