# coding:utf-8
"""
python中的类 =属性（数据）+方法
类对象，简称为类，实例对象简称为实例

面向对象有三个特性:封装,继承,多态
__new__ __init__
"""


class Foo(object):
	
	#定义一个类,说明属性相关的事
	
    x = 100
    def print_x(self):
    	#方法文档字符串
        print(Foo.x)

p =Foo()
# print(Foo.x)
# Foo.x += 1
# print(Foo.x)
# p = Foo()
# p.print_x()
# print (dir(Foo))
# print (Foo.__dict__)
print (Foo.__doc__)
# print (Foo.__name__)
# print (Foo.__module__)
# print (Foo.__bases__)
# print (p.__class__)
print (Foo.__class__)