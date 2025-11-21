#coding: utf-8
"""
排序训练
"""

list=[122131,223,2123,22,12,345,678,55433,0,5]
n=len(list)
for i in range(n):
    small =i
    for j in range(i+1,n):
        if list[j]<list[small]:
            small = j
    if small!=i:
        list[i],list[small] = list[small],list[i]
            #temp =list[i] #C语言和java语言的做法
            #list[i]=list[small]
            #list[small]=temp
print (list)
        