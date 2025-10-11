# coding:utf-8
"""
匹配全体Python长整型的字符串表示形式的集合

"""
import re
word = '2123213121111111113L'
m = re.match('\d+[L]', word)
if m is not None:
    print(m.group())
else:
    print('no any match')
