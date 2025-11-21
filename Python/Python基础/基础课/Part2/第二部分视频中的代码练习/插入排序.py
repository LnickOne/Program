#coding:utf-8
"""插入排序"""

"""
插入排序思路：将list从第0个到最后一个，按照如下
[3]
[3,88]
[3,88,76]=>[3,76,88]
[3,76,88,23]=>[3,76,23,88]

"""

list1=[3,88,76,23,998,22,888,56,39,72]

for i in range(len(list1)):
    key = list1[i] #把最小的赋值给key
    j = i - 1
    while j >-1 and list1[j] <key :
        list1[j+1] = list1 [j] #将元素往右边移动，因为key为最大的元素
        j -= 1
        #print (list1)
    list1[j+1] = key
    
print(list1)