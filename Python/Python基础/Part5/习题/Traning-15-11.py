# coding:utf-8
"""
匹配所有合法的电子邮箱地址

"""
import re

word = 'sjaksamsamxj@renyi111111.com'
m = re.match('^\w+@\w+(\.com)$', word)
if m is not None:
    print(m.group())
else:
    print("邮箱格式不合法")
