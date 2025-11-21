#coding:utf-8

#(a) 小题
def tr1(srcstr,dststr,string):
    str1=""
    str2=""
    
    if len(srcstr)==len(dststr):
        for i in dststr:
            str1=str1+i
            l=0 
        for i in string: 
            l+=1       
            if i in srcstr:# 检查前len(srcstr)位,如果有strstr的字母就替换成 dststr
                if string[l-1] in srcstr:
                    string=string[l:]
                    str2=str1+string
        print(str2)
          
if __name__ == '__main__':
    i=input("你打算'翻译'的字符串\n")
    j=input("翻译后得到的字符串\n")
    k=input("打算进行翻译操作的字符串\n")
    tr1(i,j,k)
          
#(b)小题
    
# def tr2(srcstr,dststr,string,flag):
#         list1=""
#         list2=""
#         for i in dststr:
#             if i in flag.lower() or i in flag.upper():
#                 dststr=dststr.upper()
#                 srcstr=srcstr.upper()
#                 string=string.upper()
#                 list1=dststr
#             else:
#                 list1=dststr
#             l=0
#         for i in string:
#             l+=1
#             if i in srcstr:# 检查前len(srcstr)位,如果有strstr的字母就替换成 dststr
#                 if string[l-1] in srcstr:
#                     string=string[l:]
#                     list2=list1+string
#         print(list2)
#
#
# if __name__ == '__main__':
#     a=input("(b)小题输入")
#     b=input("(b)小题输入")
#     c=input("(b)小题输入")
#     d=input("输入参数")
#     tr2(a,b,c,d)
#
#
#
# #(c)小题
# def tr3(srcstr,dststr,string):
#     list3=""
#     list4=""
#     for i in dststr:
#         list3=list3+i
#
#     l=0
#     for i in string:
#         l+=1
#         if l == len(srcstr)-2:
#             break
#         if i in srcstr:# 检查前len(srcstr)位,如果有就替换成 dststr
#             if string[l-1] in srcstr:
#                 string=string[l:]
#                 list4=list3+string
#     print(list4)
# if __name__ == '__main__':
#     a=input("(c)小题输入")
#     b=input("(c)小题输入")
#     c=input("(c)小题输入")
#     tr3(a,b,c)
    

