# coding:utf-8

"""
只提取出时间戳字段中的月份
"""
import re


with open('redata.txt', 'r') as f:
    i = 0
    while True:
        i += 1
        content = f.readline()
        contentlist = content.split()
        if not content:
            break
        print('第', i, '行时间戳字段中的月份是', contentlist[1:2])
