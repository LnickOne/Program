# -*- coding: utf-8 -*-  
import string  

def huiwen(str):  
    if len(str)%2!=0:  
        print ("It is not a palindorom.")  
    else:  
        if cmp (str, str[::-1]) == 0:  
            print ("It is a palindorom.")  
        else:  
            print ("It is not a palindorom.")  

if __name__=='__main__':  
    str = input()  
    huiwen(str) 