# coding:utf-8
"""
python中的类 =属性（数据）+方法
类对象，简称为类，实例对象简称为实例

面向对象有三个特性:封装,继承,多态
"""


class Foo(object):
    num = 5

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def print_xy(self):
        print(self.x, self.y)

    def print_num(self):
        print(self.num)

p = Foo(3, 7)
p.print_xy()
p.print_num()
