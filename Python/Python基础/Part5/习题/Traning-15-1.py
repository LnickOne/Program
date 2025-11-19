# coding:utf-8
"""

识别下列字符串：“bat,” “bit,” “but,” “hat,” “hit,” 或 “hut”


"""

import re

# bt = 'bat|but|bit'
# m = re.match(bt, 'bat')
# m1 = re.match(bt, 'bit')
# m2 = re.match(bt, 'but')
# if m and m1 and m2 is not None:
#     print(m.group())
#     print(m1.group())
#     print(m2.group())

word = input('input: ')
m = re.match('^[bh][aiu][t]$', word)
if m is not None:
    print(m.group())
else:
    print('no any match')
