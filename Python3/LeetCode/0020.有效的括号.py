#
# @lc app=leetcode.cn id=20 lang=python3
#
# [20] 有效的括号
#
# https://leetcode.cn/problems/valid-parentheses/description/
#
# algorithms
# Easy (45.25%)
# Likes:    4850
# Dislikes: 0
# Total Accepted:    2.4M
# Total Submissions: 5.3M
# Testcase Example:  '"()"'
#
# 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。
#
# 有效字符串需满足：
#
#
# 左括号必须用相同类型的右括号闭合。
# 左括号必须以正确的顺序闭合。
# 每个右括号都有一个对应的相同类型的左括号。
# 示例 1：
# 输入：s = "()"
# 输出：true
# 示例 2：
# 输入：s = "()[]{}"
# 输出：true
# 示例 3：
# 输入：s = "(]"
# 输出：false
# 示例 4：
# 输入：s = "([])"
# 输出：true
# 示例 5：
# 输入：s = "([)]"
# 输出：false
# 提示：
# 1 <= s.length <= 10^4
# s 仅由括号 '()[]{}' 组成
# @lc code=start
class Solution:
    def isValid(self, s: str) -> bool:
        stack = []
        for ch in s:
            if ch == "(" or ch == "[" or ch == "{":
                stack.append(ch)
            elif ch == ")" or ch == "]" or ch == "}":
                if not stack:
                    return False
                elif stack:
                    element = stack.pop()
                    if element == "(" or element == "[" or element == "{":
                        if element != "(" and ch == ")":
                            return False
                        elif element != "[" and ch == "]":
                            return False
                        elif element != "{" and ch == "}":
                            return False
        return len(stack) == 0


print(Solution().isValid("{}"))
print(Solution().isValid("{]"))
print(Solution().isValid("()"))
print(Solution().isValid("()[]{}"))
print(Solution().isValid("(]"))
print(Solution().isValid("([)]"))
# @lc code=end
