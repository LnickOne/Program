# coding:utf-8
"""
python中的类 =属性（数据）+方法
类对象，简称为类，实例对象简称为实例
"""


class Foo(object):
    """带括号,继承自object,是新式类 """
    pass


class Foo2:
    """不带括号，不继承自object,是经典类"""
    pass


p = Foo()
print(p)
p.x = 7  # p有x和y两个属性
p.y = 8
Foo.z = 20
print (Foo.z)
print(p.x)
print(p.y)
print(p.z)
