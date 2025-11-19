# coding:utf-8

class Foo(object):
    def __new__(cls,*args,**kwargs):
        print ("先调用__new__方法")
        tmp = super(Foo,cls).__new__(cls,*args,**kwargs) #调用object的__new__方法
        print (type(tmp))
        print (id(tmp))
        print (isinstance(tmp,Foo))
        return tmp

    def __init__(self):
        print ("后调用__init__方法")
        print (id(self))

p = Foo()
print("-------")
print(id(p))
print(type(p))