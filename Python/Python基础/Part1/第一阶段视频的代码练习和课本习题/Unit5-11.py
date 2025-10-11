#coding: utf-8

def num():  
    num1=[]  #偶数  
    num2=[]  #奇数  
    for i in range(20):  
        if i %2 == 0:  
            num1.append(i)  
        else:  
            num2.append(i)  
    print ('偶数：')  
    for i in num1:  
        print (i)  
    print ('\n奇数：')  
    for i in num2:  
        print (i)      



if __name__=='__main__':  
    num()  