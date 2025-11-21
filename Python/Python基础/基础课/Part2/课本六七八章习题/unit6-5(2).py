# -*- coding: utf-8 -*-  
import string  

str1 = input()  
str2 = input()  

for i,j in zip(str1,str2):  
    if i is not j:  
        print ("no")  
        break  
else:  
    print ("yes")