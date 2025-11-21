# coding:utf-8
"""
python中的类 =属性（数据）+方法
类对象，简称为类，实例对象简称为实例

面向对象有三个特性:封装,继承,多态
__new__ __init__
"""

class Foo(object):
	x = 1
	list1 =[1]
Foo.x += 1
#print (Foo.x)
p = Foo()
#print(p.x)
p.x += 1
p.list1.append(6)
print (p.list1)
print (Foo.list1)
print (p.x)
print (Foo.x)

#此处结论是如果是可变类型对象,通过实例修改可以成功.如果不是可变类型对象,通过实例修改就不行