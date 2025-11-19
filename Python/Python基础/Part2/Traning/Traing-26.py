#coding:utf-8
import random

N=random.randint(0,10)
n=random.randrange(0,10)

listA=[]
listB=[]
for i in range(N+1):
    listA.append(i)

for i in range(n+1):
    listB.append(i)

print(listA)
print(listB)

listC=[]
for j in listA and listB:
    if j in listA and j in listB:
        listC.append(j)
print("A&B((A交集B)为",listC)


listD=[]
for j in listA:
    listD.append(j)
for k in listB:
    if k in listA:
        continue
    elif k not in listA:
        listD.append(k)
    


print("A|B (A并集B)为",listD)
