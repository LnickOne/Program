#coding:utf-8
from functools import reduce

def average(num):
    numlist=range(num)
    print ('平均值是: ', (reduce((lambda x,y:x+y),numlist))/len(numlist))
average(5)
