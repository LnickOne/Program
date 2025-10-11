#coding:utf-8
def f (n):
    flist=[0,1,1]
    if n== 1 or n ==2 :
        return 1
    
    else :
        for i in range(2,n):
            flist.append(f(i)+flist[i-1])
    return flist[n]
print ("你想要看第斐波那契数列的第几个")
n = int (input())
print (f(n))