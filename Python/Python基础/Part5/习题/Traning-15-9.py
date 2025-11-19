# coding:utf-8
"""
匹配全体Python浮点型的字符串表示形式的集合。


"""
import re
word = '1.4541515471524848'
m = re.match('.*\..*', word)
if m is not None:
    print(m.group())
else:
    print('no any match')
