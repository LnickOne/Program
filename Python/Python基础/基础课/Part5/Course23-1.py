#coding:utf-8
"""
命名空间 namespace 
名称到对象的映射
"""

import sys
sys.path.append(r"Users/manki/Desktop/Part5/")
import P37


# print("hello python")


class Foo(object):
    pass

def foo():
    print ("in foo()")


class Time60(object):
    pass

# for i in sys.path:
#     print(i)

p = P37.Time60(10,30)
print (p)
p2= Time60()
#print(p2)

print (globals())