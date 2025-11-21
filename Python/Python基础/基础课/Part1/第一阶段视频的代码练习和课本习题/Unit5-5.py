# -*- coding: utf-8 -*-   
def money(num):  
    num = int (num)
    num = num *100  
    a = num // 25  
    b = (num - a *25)//10  
    c = (num - a* 25 - b *10) //5  
    d = (num -a * 25 - b * 10 - c * 5)  
    return a+b+c+d  
      
if __name__=='__main__':  
    n = input()  
    print (money(n)) 