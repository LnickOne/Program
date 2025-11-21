# coding:utf-8

"""
__new__ 和 __init__区别
"""

class Foo(object):
    def __init__(self,x):
        self.x = x

a = Foo(5)
tmp = Foo.__new__(Foo,5) #__new__ 这个方法在object这个父类里面,Foo继承得到这个方法,new这个方法第一个参数是类Foo.   这样整体的意思是返回一个对象
#__new__ 返回一个实例，这个实例供__init__调用
tmp.__init__(5) #对象在这里初始化
a = tmp  #初始化好之后，将tmp赋给a
print (a.x)

# print (tmp)
# print (type(tmp))

 