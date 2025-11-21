#coding:utf-8

#生成要排列的数字列表
list1=[]
n=input("你需要排列几个数字")
n=int(n)
for k in range(n):
    N=input("请输入要排列第%d个数字\n"%(k+1))
    N=int(N)
    list1.append(N)
print("排列前的列表为",list1)

#冒泡排序数字，从大到小
n=len(list1)
i=0
while i <n:
    j = 0
    while j <n-1:
        if list1[j]<list1[j+1]:
            list1[j],list1[j+1]=list1[j+1],list1[j]
        j+=1
    i+=1   
print("排列后的列表为",list1)

#生成要排列的字母列表
list2=[]
n=input("你需要排列几个字母或者字符串")
n=int(n)
for k in range(n):
    N=input("请输入要排列第%d个字母或字符串\n"%(k+1))
    list2.append(N)
print("排列前的列表为",list2)

#冒泡排序字母，从a到z
n=len(list2)
i=0
while i <n:
    j = 0
    while j <n-1:
        if list2[j]<list2[j+1]:
            list2[j],list2[j+1]=list2[j+1],list2[j]
        j+=1
    i+=1   
print("排列后的列表为",list2)