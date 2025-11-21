#coding:utf-8
"""
while循环和print
1
1 2
1 2 3
1 2 3 4
1 2 3 4 5 
1 2 3 4 5 6
1 2 3 4 5 6 7
"""

num = 7
i =1
while i <= num:
    i = i+1
    j = 1
    while j<i:
        print (j,end=' ') 
        j=j+1
    print()

