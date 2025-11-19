# coding:utf-8


class Foo(object):
    __slots__ = ("x","y","z") #插槽的概念,节省内存空间,不弄乱


    def __init__(self,x,y,z):
        self.x = x
        self.y = y
        self.z = z

p = Foo(5,6,7)
#print (p.__dict__)
#print (dir(p ))
p.z = 100
print (p.z)