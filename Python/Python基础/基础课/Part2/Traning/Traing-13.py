#coding:utf-8
import keyword
 
keywords = keyword.kwlist  

print ("welcome to the identifier checker v1.0，欢迎来到测试字符串v1.0版") #课本P111的例子
myinput = input('你想测试的对象为？') 

if len(myinput)>1:
    print("你输入的字符串长度为:",len(myinput)) 
if myinput in keywords:  
    print("你输入的字符串是python关键词")   
if len(myinput)==1:
    print("你输入的字符串长度为1")
    
