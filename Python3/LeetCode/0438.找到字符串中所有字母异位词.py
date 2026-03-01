#
# @lc app=leetcode.cn id=438 lang=python3
#
# [438] 找到字符串中所有字母异位词
#
# @lc code=start
from typing import List


class Solution:
    def findAnagrams(self, s: str, p: str) -> List[int]:
        if len(p) > len(s):
            return []
        result = []
        s_map = {}
        p_map = {}
        # 处理第一个窗口
        for i in range(0, len(p)):
            s_map[s[i]] = s_map.get(s[i], 0) + 1
            p_map[p[i]] = p_map.get(p[i], 0) + 1
        if s_map == p_map:
            result.append(0)
        # 处理后续窗口
        k = len(p)
        for i in range(k, len(s)):
            s_map[s[i]] = s_map.get(s[i], 0) + 1
            s_map[s[i - k]] = s_map.get(s[i - k], 0) - 1
            if s_map.get(s[i - k]) == 0:
                del s_map[s[i - k]]
            if s_map == p_map:
                result.append(i - k + 1)
        return result


print(Solution().findAnagrams("cbaebabacd", "abc"))
print(Solution().findAnagrams("abab", "ab"))
print(Solution().findAnagrams("baa", "aa"))
print(Solution().findAnagrams("aaaaaaaaaa", "aaaaaaaaaaaaa"))
print(Solution().findAnagrams("abacbabc", "abc"))

# @lc code=end
