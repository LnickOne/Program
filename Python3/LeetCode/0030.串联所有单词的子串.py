# @lc app=leetcode.cn id=30 lang=python3
# [30] 串联所有单词的子串
# https://leetcode.cn/problems/substring-with-concatenation-of-all-words/description/
# algorithms
# Hard (38.19%)
# Likes:    1323
# Dislikes: 0
# Total Accepted:    289.8K
# Total Submissions: 758.7K
# Testcase Example:  '"barfoothefoobarman"\n["foo","bar"]'
# 给定一个字符串 s 和一个字符串数组 words。 words 中所有字符串 长度相同。
# s 中的 串联子串 是指一个包含  words 中所有字符串以任意顺序排列连接起来的子串。
# 例如，如果 words = ["ab","cd","ef"]， 那么 "abcdef"， "abefcd"，"cdabef"，
# "cdefab"，"efabcd"， 和 "efcdab" 都是串联子串。 "acdbef" 不是串联子串，因为他不是任何 words 排列的连接。
# 返回所有串联子串在 s 中的开始索引。你可以以 任意顺序 返回答案。
# 示例 1：
# 输入：s = "barfoothefoobarman", words = ["foo","bar"]
# 输出：[0,9]
# 解释：因为 words.length == 2 同时 words[i].length == 3，连接的子字符串的长度必须为 6。
# 子串 "barfoo" 开始位置是 0。它是 words 中以 ["bar","foo"] 顺序排列的连接。
# 子串 "foobar" 开始位置是 9。它是 words 中以 ["foo","bar"] 顺序排列的连接。
# 输出顺序无关紧要。返回 [9,0] 也是可以的。
# 示例 2：
# 输入：s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
# 输出：[]
# 解释：因为 words.length == 4 并且 words[i].length == 4，所以串联子串的长度必须为 16。
# s 中没有子串长度为 16 并且等于 words 的任何顺序排列的连接。
# 所以我们返回一个空数组。
# 示例 3：
# 输入：s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
# 输出：[6,9,12]
# 解释：因为 words.length == 3 并且 words[i].length == 3，所以串联子串的长度必须为 9。
# 子串 "foobarthe" 开始位置是 6。它是 words 中以 ["foo","bar","the"] 顺序排列的连接。
# 子串 "barthefoo" 开始位置是 9。它是 words 中以 ["bar","the","foo"] 顺序排列的连接。
# 子串 "thefoobar" 开始位置是 12。它是 words 中以 ["the","foo","bar"] 顺序排列的连接。
# 提示：
# 1 <= s.length <= 10^4
# 1 <= words.length <= 5000
# 1 <= words[i].length <= 30
# words[i] 和 s 由小写英文字母组成
# @lc code=start
from typing import List


class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        res = []
        if not s or not words:
            return res

        # 计算单词长度和总长度
        word_len = len(words[0])
        words_count = len(words)
        total_len = word_len * words_count
        s_len = len(s)

        # 特殊情况处理
        if total_len > s_len:
            return res

        # 统计 words 中每个单词的出现次数
        from collections import defaultdict

        words_freq = defaultdict(int)
        for word in words:
            words_freq[word] += 1

        # 遍历所有可能的起始位置
        for i in range(s_len - total_len + 1):
            # 统计当前子串中每个单词的出现次数
            current_freq = defaultdict(int)
            match = True

            # 检查子串是否由 words 中的单词组成
            for j in range(words_count):
                # 提取当前单词
                start = i + j * word_len
                word = s[start : start + word_len]

                # 如果单词不在 words 中，或者出现次数超过 words 中的次数
                if word not in words_freq or current_freq[word] >= words_freq[word]:
                    match = False
                    break

                current_freq[word] += 1

            # 如果所有单词都匹配，记录起始位置
            if match:
                res.append(i)

        return res


print(Solution().findSubstring("barfoothefoobarman", ["foo", "bar"]))
print(
    Solution().findSubstring(
        "wordgoodgoodgoodbestword", ["word", "good", "best", "word"]
    )
)
print(Solution().findSubstring("barfoofoobarthefoobarman", ["bar", "foo", "the"]))
# @lc code=end
