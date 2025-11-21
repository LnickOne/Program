# coding:utf-8
"""
python中的类 =属性（数据）+方法
类对象，简称为类，实例对象简称为实例

面向对象有三个特性:封装,继承,多态
__new__ __init__
"""


class Foo(object):
    num = 10

    def __init__(self, x, y=8):
        self.x = x
        self.y = y

    def print_x_y(self):
        return self.x + self.y + self.num


p = Foo(5)
p2 =Foo(7)
print (Foo.num)
print (p.num)
print (p2.num)
# print(p.print_x_y())
# print (dir(p))
# print (p.__dict__)
# print (p.__class__)
# print (vars(p))