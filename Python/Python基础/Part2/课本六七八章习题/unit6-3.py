# -*- coding: utf-8 -*-  
import string  


num1 = []  
num2 = []  
num = input()  

for i in num:  
    num1.append(i)
    num2.append(i)  


num1.sort()  
num1.reverse()  
num2.sort()  
num2.reverse()  

print (num1)  
print (num2)