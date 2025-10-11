# coding:utf-8


"""
提取每行中完整的电子邮箱地址
"""
import re


with open('redata.txt', 'r') as f:
    i = 0
    while True:
        i += 1
        content = f.readline()
        m = re.match(r'(.*)::(.*)::(\d+)', content)

        if m is not None:
            print('第', i, '行完整的电子邮箱地址是', m.group(2))
        if not content:
            break
