#coding:utf-8

#(1)字典的键按字母顺序排序
dic1={'protocol':'tcp','ip':'127.0.0.0.1','user':'client','link':'hostname'}
k=sorted(dic1.keys())
print("按字母排序的键为",k)

#(2)将排好序的键 输出对应的值
list1=sorted(dic1.keys())
for i in list1:
    print("排好序的键为%s对应的值为%s"%(i,dic1[i]))

#(3)将字典中的值排好序，输出值以及对应的键. 思路是重新建立一个字典，然后让键值互换，将排列好的值变成键后，就是对应的键了
list2= sorted(dic1.values())
print("排好序的值顺序为",list2)

di = {value:key for key,value in dic1.items()}
for i in list2:
    print(di[i])