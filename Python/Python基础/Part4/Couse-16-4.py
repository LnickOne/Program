# coding:utf-8
"""
python中的类 =属性（数据）+方法
类对象，简称为类，实例对象简称为实例

面向对象有三个特性:封装,继承,多态
__new__ __init__
"""


class Person(object):
    def __init__(self, name, age, height):
        self.age = age
        self.name = name
        self.height = height
        dict1 = {"work":"python程序员","收入":"1万5"}
        self.zhiye = dict1

    def what_your_name(self):
        print("My name is" + self.name)

    def how_old(self):
        print("I am %d years old" % (self.age))

    def how_height(self):
        print("{1}有{0}米".format(self.height,self.name ))

    def print_salary(self):
        for key in self.zhiye:
            print (key,self.zhiye[key])



p1 = Person("Tom", 25, 1.8)
p1.what_your_name()
p1.how_old()
p1.how_height()
p1.print_salary()
 