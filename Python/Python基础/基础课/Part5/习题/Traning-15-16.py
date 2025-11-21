# coding:utf-8
"""
修改gendata.py的代码，使数据直接写入文件redata.txt中，而不是输出到屏幕上
课本P458上的代码
"""

import random
import string
import sys
import time
doms = ('com', 'edu', 'net', 'org', 'gov')
f1 = open('redata.txt', 'w')
for i in range(random.randint(5, 10)):
    dtint = random.randint(0, int(time.time())-1)  # pick data
    dtstr = time.ctime(dtint)  # date string
    shorter = random.randint(4, 7)  # login shorter
    em = ''
    for j in range(shorter):  # generate login
        em += random.choice(string.ascii_lowercase)

    longer = random.randint(shorter, 12)  # domain longer
    dn = ''
    for j in range(longer):  # create domain
        dn += random.choice(string.ascii_lowercase)

    f1.write('%s::%s@%s.%s::%d-%d-%d\n' %
             (dtstr, em, dn, random.choice(doms), dtint, shorter, longer))

    # print('%s::%s@%s.%s::%d-%d-%d' %
    #       (dtstr, em, dn, random.choice(doms), dtint, shorter, longer))
f1.close()
