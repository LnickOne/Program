# coding:utf-8
import re

a = '800-555-1212'
b = '555-1212'
c = '(800) 555-1212'
m = re.search(r'.*', c)

if m is not None:
    print(m.group())
else:
    print('no any match')
