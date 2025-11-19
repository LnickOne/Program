# coding:utf-8


class Foo(object):
    __slots__ = ("x", "y", "z")  # 插槽的概念,节省内存空间,不弄乱

    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z


p = Foo(5, 6, 7)
print(p.y)
# print (p.__dict__) #槽和字典属性不能同时存在

#print (dir(p ))
# p.w = 100
# print (p.w) #定义槽以后，就不能随便定义变量了,会限定属性
