# coding:utf-8
"""
匹配全体Python整型的字符串表示形式的集合

"""
import re
word = '2123213121111111113'
m = re.match('\d+', word)
if m is not None:
    print(m.group())
else:
    print('no any match')
