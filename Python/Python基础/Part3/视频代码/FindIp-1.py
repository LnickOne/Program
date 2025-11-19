# coding:utf-8
# 传统法,如果文件特别大
file1 = open("ip.txt", "r")
file2 = open("ipout-1.txt", "w")
list1 = []
while 1:
    line = file1.readline()
    s = line.find("Mozilla/5.0")
    s1 = line.find("Sogou web spider/4.0")
    if s >= 0:
        list1.append(line[:s-1].strip())
    if s1 >= 0:
        list1.append(line[:s1-1].strip())
    if not line:
        break

list2 = sorted(list(set(list1)))
print(len(list2))
print(list2)


for i in list2:
    file2.write(i+"\n")

file1.close()
file2.close()
