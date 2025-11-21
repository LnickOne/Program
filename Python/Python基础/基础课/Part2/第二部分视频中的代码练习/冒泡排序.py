#coding:utf-8
"""
冒泡排序
"""

list=[1,2,3,4,7,8,5,9,122,31314,665,666,667,775,899,778,997,443,77,88,55]

for i in range(len(list)-1):
    flag = 1
    for j in range(len(list)-1-i):
        if list[j] >list[j+1]:
            list[j],list[j+1]=list[j+1],list[j]
            flag = 0
    if flag:
        break
print(list)