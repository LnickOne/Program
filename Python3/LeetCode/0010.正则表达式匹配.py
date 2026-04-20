#
# @lc app=leetcode.cn id=10 lang=python3
#
# [10] 正则表达式匹配
#
# 思路：使用递归实现正则表达式匹配
# 1. 如果模式为空，则返回输入是否为空
# 2. 如果模式不为空，则判断第一个字符是否匹配
# 3. 如果第一个字符匹配，则继续匹配剩余的字符
# 4. 如果第一个字符不匹配，则返回False 或者 继续匹配剩余的字符
# @lc code=start
class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        if not p:
            return not s
        first_match = bool(s) and p[0] in {s[0], "."}
        if len(p) >= 2 and p[1] == "*":
            return self.isMatch(s, p[2:]) or first_match and self.isMatch(s[1:], p)
        else:
            return first_match and self.isMatch(s[1:], p[1:])


print(Solution().isMatch("aa", "a"))
print(Solution().isMatch("aa", "a*"))
print(Solution().isMatch)

# @lc code=end
