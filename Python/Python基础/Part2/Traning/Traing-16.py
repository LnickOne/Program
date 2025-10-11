#coding:utf-8

def EngNum(n):
    list1=[]
    for i in n:
        list1=n
    k=""
    j=""
    for i in list1:
        i=int(i)
        if i ==0:
            j="zero"
        if i==1:
            j="one"
        if i==2:
            j="two"
        if i==3:
            j="three"
        if i==4:
            j="four"
        if i ==5:
            j="five"
        if i==6:
            j="six"
        if i==7:
            j="seven"
        if i==8:
            j="eight"
        if i==9:
            j="nine"                              
        k=k+"-"+j
        if k[0]=="-":
            k=k[1:]

    print(k)

if __name__=='__main__':
    n=input("输入数字\n")
    EngNum(n)