# coding:utf-8
"""

"""


class Foo(object):

    def __init__(self, x):
        self.x = x

    def __getattr__(self, name):
        if name == "age":
            return 40
        else:
            raise( ArithmeticError, name)


p = Foo(5)
#print (getattr(p,'x'))
# print(p.age)   
print (p.age)
print (p.x)    # print (getattr(p,'x')) = print (p.x)  这个是等式 
print (getattr(p,'x'))  #就是实例属性里面有 x 就会钩到方法__getattr__了
print (getattr(p,'age'))#实例属性没有 age, 就会钩到__getattr___