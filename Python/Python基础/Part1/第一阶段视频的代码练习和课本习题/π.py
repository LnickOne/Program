#coding:utf-8
"""
求π 
pi = 4/1 - 4/3 + 4/5 - 4/7

1+1-1=1
2+2-1=3
3+3-1=5
直到最后一项的绝对值小于10的-6为止
"""

import math
flag = 4.0
sumpi=0
n=1

while math.fabs(flag/(n+n-1)) >=1e-6:
    sumpi = sumpi +flag/(n+n-1)
    n = n+1
    flag = -flag 
"""
一正一负
"""
    
print (sumpi)