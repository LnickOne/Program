#coding:utf-8
import string
loweralphas=string.ascii_lowercase
upperalphas=string.ascii_uppercase

def change(str1):
    str2=""
    for i in str1:
        if i in loweralphas:
            i=i.upper()
            str2=str2+i
        elif i in upperalphas:
            i=i.lower()
            str2=str2+i
        else:
            str2=str2+i
    print(str2)


if __name__=='__main__':
    n=input("输入字符串\n")
    change(n)