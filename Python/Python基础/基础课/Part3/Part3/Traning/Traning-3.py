#coding:utf-8

import string

zhaohengxian = string.punctuation

file1 = open("gettysburg.txt","r")
file2 = open("wordout.txt","w")
file3 = open("wordout1.txt","w")
file4 = open("wordout2.txt","w")
list1 = []

#用字典实现一遍
dict1 ={}
while True:
    pass


while 1:
    line = file1.readline()
    line1 = line.split()
    s = line.find("/n")
    if s !=1:
        i=0
        while i <len(line1):         
            if line1[i] not in zhaohengxian:
                list1.append(line1[i].strip(',').strip('.').strip(':'))
            i+=1
    if not line :
        break   
 
list2 = (list1)
               
print ("所有的单词个数为",len(list2))
print (list2)

for i in list2:
    file2.write(i+"\n")

list3 = sorted(list(set(list1)))
print ("删掉重复单词后剩余的个数为",len(list3))
print (list3)


for i in list3:
    file3.write(i+"\n")

file1.close()
file2.close()
file3.close()