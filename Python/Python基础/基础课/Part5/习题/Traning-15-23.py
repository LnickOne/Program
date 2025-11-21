# coding:utf-8

"""
只提取出时间戳字段中的值(格式:HH:MM:SS)
"""
import re
f1 = open('redata.txt', 'r')
i = 0
while True:

    content = f1.readline()
    i += 1
    m = re.match(r'(.*)::(.*)::(\d+)', content)
    if m is not None:
        year = m.group(1).split()
        print('第', i, '时间戳字段中的值(格式:HH:MM:SS)是', year[3])
    if not content:
        break
