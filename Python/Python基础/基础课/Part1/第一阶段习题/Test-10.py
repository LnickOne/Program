#coding: utf-8
while 1:
    for x in range(6):
        y = 2 * x + 1
        print(y)
        if y>9:
            break
# 把x替换成4，会报错，没有for 4 in range(6)的语法