# coding:utf-8
"""
写一个正则表达式表示标准日历上其他的三个月(十月,十一月,十二月)

"""
import re


word = '10 11 12'
m = re.match('((1?[0-2].+)*)', word)
if m is not None:
    print(m.group())
else:
    print("月份不合法")
