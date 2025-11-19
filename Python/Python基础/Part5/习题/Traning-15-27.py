# coding:utf-8

"""
提取出时间戳中的月、日、年，并按照格式“月 日，年”输出，且每行仅遍历一次。
 
"""
import re
# f1 = open('redata.txt', 'r')
# i = 0
# while True:
#     content = f1.readline()
#     i += 1
#     m = re.match(r'(.*)::(.*)::(\d+)', content)
#     # print(m.group(1))
#     GroupList = m.group(1).split()
#     del GroupList[0]
#     del GroupList[2]
#     print('第', i, '行提取出时间戳中的月、日、年，并按照格式“月 日，年”输出', GroupList[0:3])
#     if not content:
#         break

with open('redata.txt', 'r') as f:
    for line in f:
        m = re.match(r'(\w+) (\w+ \w+) .+ (\d+)', line)
        if m is not None:
            print(m.group(2), m.group(3))
