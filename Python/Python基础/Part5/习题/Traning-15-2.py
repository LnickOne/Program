# coding:utf-8
"""

匹配用一个空格分隔的任意一对单词，比如名和姓。


"""
import re

word = 'zhang san'
m = re.match(r'.+\s.+', word)
if m is not None:
    print(m.group())
else:
    print("not match")
