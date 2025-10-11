# coding:utf-8
"""
匹配一个街道地址
"""
import re
word = '1180 Bordeaus Drive'
word1 = '3120 De la Cruz Boulevard'
m = re.match('.+', word1)
if m is not None:
    print(m.group())
else:
    print('no any match')
