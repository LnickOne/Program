#
# @lc app=leetcode.cn id=12 lang=python3
#
# [12] 整数转罗马数字
#
# @lc code=start
class Solution:
    def intToRoman(self, num: int) -> str:
        result = ""
        symbols = [
            "M",
            "CM",
            "D",
            "CD",
            "C",
            "XC",
            "L",
            "XL",
            "X",
            "IX",
            "V",
            "IV",
            "I",
        ]
        values = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1]
        for i in range(len(values)):
            while num >= values[i]:
                num -= values[i]
                result += symbols[i]
        return result


print(Solution().intToRoman(3))
print(Solution().intToRoman(4))
print(Solution().intToRoman(9))
print(Solution().intToRoman(58))
print(Solution().intToRoman(1994))
print(Solution().intToRoman(1000))


# @lc code=end
