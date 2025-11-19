# coding:utf-8
"""
命名空间 namespace
是名称到对象的映射
全局命名空间,局部命名空间,内置命名空间(dir (__builtins__))
"""

import sys
sys.path.append(r"Users/manki/Desktop/Part5/")
from P37.Couse213 import Time60
#num = 10

print("hello python")


class Foo(object):
    pass


def foo():
    num_in_foo = 10
    print ("in foo()")
    #print (locals())

# class Time60(object):
#     pass

# for i in sys.path:
#     print(i)

p = Time60(10,30)
print (p)


# print (globals())
# foo()
# print (locals())