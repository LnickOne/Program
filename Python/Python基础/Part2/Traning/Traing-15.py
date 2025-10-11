#coding:utf-8
import string
alphas=string.ascii_letters
num=string.digits
symbol=string.punctuation

str1 = input("Enter a string\n")
for i in str1:
       j=0
       if i in alphas or num or symbol and i!=" ": #当i 遍历到第一个非空格时候执行
              j+=1
              if str1[j-1] == ' ':
                     if str1[-1] == ' ':
                            str1 = str1[j:-1] #如果字符串str[0] 是空格 而且str[-1] 也是空格，str=str[1]和str[-2] 之间的,相当于持续删除最前面的空格
                     else:
                            str1 = str1[j:]#如果字符串str[0] 是空格 而且str[-1] 不是空格，那就直接str=str[1]到最后
                     print(str1)
              elif str1[-1] == ' ' :
                     str1 = str1[:-1] #持续删除最后一个空格
print (str1)
