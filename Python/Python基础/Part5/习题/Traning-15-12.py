# coding:utf-8
"""
匹配所有合法的Web网站地址（URL）

"""
import re

word = 'https://www.huanggepython.com'
m = re.match(r'^.*www\.\w+(\.com)$', word)
if m is not None:
    print(m.group())
else:
    print("Web网站不合法")
