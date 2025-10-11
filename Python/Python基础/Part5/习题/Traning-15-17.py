# coding:utf-8
"""
统计生成的redata.txt文件中，星期中的每一天出现的次数,统计各个月份出现的次数

"""

import random
import string
import sys
import time
doms = ('com', 'edu', 'net', 'org', 'gov')
f1 = open('redata.txt', 'w')

for i in range(random.randint(5, 10)):
    dtint = random.randint(0, int(time.time()) - 1)  # pick data
    dtstr = time.ctime(dtint)  # date string
    shorter = random.randint(4, 7)  # login shorter
    em = ''
    for j in range(shorter):  # generate login
        em += random.choice(string.ascii_lowercase)

    longer = random.randint(shorter, 12)  # domain longer
    dn = ''
    for j in range(longer):  # create domain
        dn += random.choice(string.ascii_lowercase)
    # print('%s::%s@%s.%s::%d-%d-%d' %
    #       (dtstr, em, dn, random.choice(doms), dtint, shorter, longer))

    s = '%s::%s@%s.%s::%d-%d-%d\n' % (dtstr, em, dn, random.choice(doms), dtint, shorter, longer)
    f1.write(s)
f1.close()


f2 = open('redata.txt', 'r')
dict1 = {}
dict2 = {}
while True:
    content = f2.readline()
    ContentList = content.split()
    s = content.find('/n')
    if s != 1:
        for key in ContentList[:1]:
            if key in dict1:
                dict1[key] += 1
            else:
                dict1[key] = 1
        for key in ContentList[1:2]:
            if key in dict2:
                dict2[key] += 1
            else:
                dict2[key] = 1
    if not content:
        break
print(dict1)
print(dict2)
f2.close()

# 正则表达式的匹配统计方法
import re

week = {}.fromkeys(('Mon', 'Tue', 'Wed', 'Thu', 'Fri',
                    'Sat', 'Sun'), 0)  # 生成一个包含七个星期的字典
st = '|'.join(week.keys())

with open('redata.txt') as f:
    for line in f:
        m = re.match(st, line)
        if m is not None:
            week[m.group()] += 1
print(week)
