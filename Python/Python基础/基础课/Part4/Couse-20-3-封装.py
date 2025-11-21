# coding:utf-8
"""
封装和隐藏,私有化  ,封装就是把属性和方法写在一起,把他们隐藏起来,留一些接口(方法)给别人调用
隐藏就是放到类里面

私有化就是通过两个下横线给变量弄成私有
"""


class Foo(object):
    __num =10
    def __init__(self, x, y):
        self.__x = x
        self.y = y
        #self._z = z

    def print_x_y(self):
        print(self.__x, self.y)
        self.__printxy()

    def __printxy(self):
        print("我是私有方法")


class Foo2(Foo):
    pass


p = Foo2(5, 6 )
print(p.y)
#print(p.z)
p.print_x_y()
# p.__printxy()
print (Foo._Foo__num)