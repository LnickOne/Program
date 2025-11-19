# coding:utf-8
"""
匹配全体Python复数的字符串表示形式的集合


"""
import re
word = '1+3j 2+2j 5j 5'
m = re.match('(.*\+[\dj].*)*', word)
if m is not None:
    print(m.group())
else:
    print('no any match')
