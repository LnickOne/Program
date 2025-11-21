# coding:utf-8

"""
匹配用一个逗号和一个空格分开的一个单词和一个字母。例如英文人名中的姓和名的首字母。

"""

import re

word = 'zhang,san'
m = re.match('.+\w.+', word)
if m is not None:
    print(m.group())
