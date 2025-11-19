#coding:utf-8

file1 = open("ip.txt","r")
file2 = open("ipout-2.txt","w")
list1= []

for line in file1: #迭代打开的文件
    s = line.find("Mozilla/5.0" )
    s1=line.find("Sogou web spider/4.0")
    if s >=0:
        list1.append(line[:s-1].strip()) 
    if s1>=0:
        list1.append(line[:s1-1].strip())

list2 = sorted(list(set(list1)))
for j in list2:
    file2.write(j+"\n")

print (len(list2))
print (list2)


file1.close()
file2.close()