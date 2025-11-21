# coding:utf-8


"""

通过检查每个输出行中整型字段部分的第一个整型是否和该行开头的时间戳相匹配来验证redata.txt中的数据是否完好


"""
import re
import time

with open('redata.txt') as f1:
    for line in f1:
        m = re.match(r'(.*)::(.*)::(\d+)', line)  # 这里匹配用::分开的三块
        if m is not None:
            t1 = time.mktime(time.strptime(m.group(1)))
            t2 = float(m.group(3))

    if t1 == t2:
        print("redata.txt中的数据完好")
