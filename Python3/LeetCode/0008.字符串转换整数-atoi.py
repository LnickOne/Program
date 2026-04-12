#
# @lc app=leetcode.cn id=8 lang=python3
#
# [8] 字符串转换整数 (atoi)
#
# @lc code=start
class Solution:
    def myAtoi(self, s: str) -> int:
        if not s or len(s) == 0:
            return 0
        # 1.去除空格
        s = s.strip()
        if len(s) == 0:
            return 0
        # 2.去除负号
        sign = 1
        if s[0] == "-":
            sign = -1
            s = s[1:]
        elif s[0] == "+":
            sign = 1
            s = s[1:]
        # 3.读取数字
        result = 0
        i = 0
        while i < len(s) and s[i].isdigit():
            result = result * 10 + int(s[i]) * sign
            i += 1
            if result >= 2**31:
                return 2**31 - 1
            if result <= -(2**31):
                return -(2**31)
        return result


print(Solution().myAtoi("42"))
print(Solution().myAtoi("   -42"))
print(Solution().myAtoi("4193 with words"))
print(Solution().myAtoi("words and 987"))
print(Solution().myAtoi("-91283472332"))
print(Solution().myAtoi("0-1"))
print(Solution().myAtoi("   +0 123"))
print(Solution().myAtoi("+-12"))
# @lc code=end
