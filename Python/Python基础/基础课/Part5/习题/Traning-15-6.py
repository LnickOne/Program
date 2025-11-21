# coding:utf-8

"""

匹配简单的以www.开头，以.com结尾的web域名


"""
import re

word = 'www.huanggepython@qq.com'
m = re.match('^www.+@.+com$', word)
if m is not None:
    print(m.group())
else:
    print('no any match')

"""
附加题


"""
word = 'www.ucsc.edu'
m = re.match('.+[edu,net,com]', word)
if m is not None:
    print(m.group())
else:
    print('no any match')
