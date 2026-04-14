#
# @lc app=leetcode.cn id=17 lang=python3
# [17] 电话号码的字母组合
# https://leetcode.cn/problems/letter-combinations-of-a-phone-number/description/
# algorithms
# Medium (62.89%)
# Likes:    3152
# Dislikes: 0
# Total Accepted:    1.2M
# Total Submissions: 1.9M
# Testcase Example:  '"23"'
#
# 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
#
# 给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
# 示例 1：
# 输入：digits = "23"
# 输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
# 示例 2：
# 输入：digits = "2"
# 输出：["a","b","c"]
# 提示：
# 1 <= digits.length <= 4
# digits[i] 是范围 ['2', '9'] 的一个数字。
# @lc code=start
from typing import List


class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        result = []
        path = ""
        map = {
            "2": "abc",
            "3": "def",
            "4": "ghi",
            "5": "jkl",
            "6": "mno",
            "7": "pqrs",
            "8": "tuv",
            "9": "wxyz",
        }
        self.backtracking(0, 0, digits, map, path, result)
        return result

    def backtracking(self, start, index, digits, map, path, result):
        if len(path) == len(digits):
            result.append(path)
            return
        current_str = map[digits[index]]
        for i in range(start, len(current_str)):
            path += current_str[i]
            self.backtracking(0, index + 1, digits, map, path, result)
            path = path[:-1]
        return


print(Solution().letterCombinations("23"))
print(Solution().letterCombinations("2"))
print(Solution().letterCombinations("24"))
print(Solution().letterCombinations("27"))


# @lc code=end
