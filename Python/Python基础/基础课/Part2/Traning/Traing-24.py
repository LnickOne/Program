#coding:utf-8

#(a) 小题
import string
alphas=string.ascii_letters

def rot13(str1):
    str2=""
    for i in str1:
        if i in alphas and ord(i)>=97 and ord(i)< 110 :
            i =chr(ord(i)+13)

        elif i in alphas and ord(i)>=110 and ord(i)<=122:
            i =chr(ord(i)-13) 
        
        elif i in alphas and ord(i)>=65 and ord(i)<=77:
            i =chr(ord(i)+13)
        
        elif i in alphas and ord(i)>=78 and ord(i)<=96:
            i =chr(ord(i)-13)         
        str2=str2+i
    print(str2)


if __name__== '__main__':
    n=input("输入加密的字符串\n")
    rot13(n)


#(b) 小题
def rot14(str1):
    str2=""
    for i in str1:
        if i in alphas and ord(i)>=97 and ord(i)< 110 :
            i =chr(ord(i)+13)

        elif i in alphas and ord(i)>=110 and ord(i)<=122:
            i =chr(ord(i)-13) 
        
        elif i in alphas and ord(i)>=65 and ord(i)<=77:
            i =chr(ord(i)+13)
        
        elif i in alphas and ord(i)>=78 and ord(i)<=96:
            i =chr(ord(i)-13)         
        str2=str2+i
    print(str2)


if __name__== '__main__':
    n=input("输入解密的字符串\n")
    rot14(n)