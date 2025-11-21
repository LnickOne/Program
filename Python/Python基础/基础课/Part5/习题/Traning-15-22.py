# coding:utf-8

"""
只提取出时间戳字段中的年份
"""
import re
f1 = open('redata.txt', 'r')
i = 0
while True:

    content = f1.readline()
    i += 1
    m = re.match(r'(.*)::(.*)::(\d+)', content)  # 这里匹配用::分开的三块
    if m is not None:
        year = m.group(1).split()
        print('第', i, '行时间戳字段中的年份是', year[4])
    if not content:
        break
