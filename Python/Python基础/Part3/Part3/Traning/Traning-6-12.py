#coding:utf-8

import time
def timeit(func,*nkwargs,**kwargs):
    try:
        start=time.clock()
        retval=func(*nkwargs,**kwargs)
        end=time.clock()
        result=(True,retval,end-start)
    except (Exception):
        result=(False)
    return result
 
def test():
    funcs=(int,int,float)
    vals=(1234,12.34,'1234','12.34')
    for eachFunc in funcs:
        print ('-'*80)
        for eachVal in vals:
            retval=timeit(eachFunc,eachVal)
            if retval:
                print ('%s(%s)='%(eachFunc.__name__,eachVal),retval[1])
                print ('this func cost %s secs' % retval[2])
            else:
                print ('%s(%s)=FAILED: ' %(eachFunc.__name__,eachVal),retval)
 
test()
