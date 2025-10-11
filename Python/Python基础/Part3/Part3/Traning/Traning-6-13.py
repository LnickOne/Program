#coding:utf-8
from functools import reduce
import time
#(a)小题
def mult (x,y):
    return x*y

#(b)小题
def myreduce (n):
    return reduce(mult,range(1,n+1))


#(c)小题
def myreduce (n):
    return reduce(lambda x,y:x*y,range(1,n+1))


#(d)小题

def factorial(n):
    if n == 0 or n == 1:
        return 1
    else :
        return n * factorial(n-1)


def timeit(func,*nkwargs,**kwargs):
    try:
        start=time.clock()
        retval=func(*nkwargs,**kwargs)
        end=time.clock()
        result=(True,retval,end-start)
    except Exception:
        result=(False)
    return result


def iteration(n):
    sum=1
    if n==0 or n==1:
        return 1
    else:
        for i in range(1,n+1):
            sum*=i
    return sum



def test(jiecheng):
    jiecheng = int (jiecheng)
    eachVal=jiecheng
    
    funcs=(iteration,myreduce,factorial)
    for eachFunc in funcs:
        print ('-'*60)
        retval=timeit(eachFunc,eachVal)
        if retval:
            print ('%s(%s)='%(eachFunc.__name__,eachVal),retval[1])
            print ('this func cost %s secs' % retval[2])
        else:
            print ('%s(%s)=FAILED: ' %(eachFunc.__name__,eachVal),retval)

if __name__ == '__main__':
    n = input ('输入几的阶乘')
    test(n)
    