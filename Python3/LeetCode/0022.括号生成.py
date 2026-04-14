# @lc app=leetcode.cn id=22 lang=python3
#
# [22] 括号生成
#
# https://leetcode.cn/problems/generate-parentheses/description/
#
# algorithms
# Medium (79.08%)
# Likes:    3971
# Dislikes: 0
# Total Accepted:    1.2M
# Total Submissions: 1.5M
# Testcase Example:  '3'
#
# 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
# 示例 1：
# 输入：n = 3
# 输出：["((()))","(()())","(())()","()(())","()()()"]
# 示例 2：
# 输入：n = 1
# 输出：["()"]
# 提示：
# 1 <= n <= 8
# @lc code=start
from typing import List


class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        result = []
        path = ""
        self.backtracking(0, 0, n, path, result)
        return result

    def backtracking(self, left, right, n, path, result):
        if len(path) == n * 2:
            result.append(path)
            return
        if left < n:
            left += 1
            path += "("
            self.backtracking(left, right, n, path, result)
            path = path[: len(path) - 1]
            left -= 1
        if right < left:
            right += 1
            path += ")"
            self.backtracking(left, right, n, path, result)
            path = path[: len(path) - 1]
            right -= 1
        return


print(Solution().generateParenthesis(3))
print(Solution().generateParenthesis(1))

# @lc code=end
