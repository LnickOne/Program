#coding:utf-8
list =[1,6,2,6,7,5,7,9,123222,11,344,43311,2234,1123,44456678]
n = len(list)
i= 0
while i <n-1:
    j = 0
    flag = 1
    while j <n-1-i:
        if list[j]<list[j+1]:
            list[j],list[j+1]=list[j+1],list[j]
            flag = 0
        j+=1
        print(list)
    i+=1
    print("第{0}轮循环交换完成".format(i))
    if flag :
        break
print("排列完的列表为",list)
    
    