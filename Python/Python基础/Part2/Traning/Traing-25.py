#coding:utf-8
import random

N=random.randint(1,100)
n=random.randint(0,(2**10)-1)

print("生成",N,"个数字的列表")
list1=[]    
for i in range(0,n):
    list1.append(i) # 生成list1 

k=0
list2=[]
while k<N:
    list2.append(random.choice(list1)) #在list1中选N个数
    k+=1

#对list2 冒泡排序，从大到小
i=0
while i<len(list2):
    j=0
    while j<len(list2)-1:
        if list2[j]<list2[j+1]:
            list2[j],list2[j+1]=list2[j+1],list2[j]
        j+=1
    i+=1
print(list2)
