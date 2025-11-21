# -*- coding: utf-8 -*-  
import string  
import keyword  

alphas = string.ascii_letters + "_"
nums = string.digits  
keywords = keyword.kwlist  

print ("welcome to the identifier checker v1.0")
print ("testees must be at least 2 chars long")
myinput = input('identifier to test ? ')  

if myinput in keywords:  
    print ("okay as an keyword")
else:  
    alphasnums = alphas + nums  
    if len(myinput) == 1:  
        if myinput in alphasnums:  
            print ("okay as an identifier") 
        else:  
            print ("invaild: remaining symbols must be alphanumeric")  
    else:  
        if myinput[0] not in alphas:  
            print ("invaild: first symbol must be  alphabetic ")     
        else:  
            for otherchar in myinput[1:]:  
                if otherchar not in alphasnums:  
                    print ("invaild: remaining symbols must be alphanumeric")  
                    break  
            else:  
                print ("okay as an identifier")