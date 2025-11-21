#coding:utf-8
"""
选择排序练习
选择排序：将剩下的每一个元素和没有比过的做比较，如果小/大，就交换。
"""
list = [7,9,3,4,11,456,34,12,87,222,111,4,99]

n = len (list)

for i in range(n):
    small = i
    for j in range(i+1,n):
        if list[j]<list[small]:
            small = j
    if small !=i : #说明找到的元素，i索引下的元素要小，然后进行交换
        list[i],list[small] = list[small],list[i]
print (list)