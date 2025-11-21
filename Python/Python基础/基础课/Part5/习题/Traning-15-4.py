# coding:utf-8


"""
匹配所有合法的python标识符

python的合法标识符定义:
1.python中的标识符是区分大小写的。
2.标示符以字母或下划线开头，可包括字母，下划线和数字。
3.以下划线开头的标识符是有特殊意义的。

"""
import re

word = input("input: ")

m = re.match('^ [\s+_\w\s+]*', word)

if m is not None:
    print(m.group())
else:
    print('not match')
