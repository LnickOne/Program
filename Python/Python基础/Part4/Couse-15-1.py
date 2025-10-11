# coding:utf-8
"""
python中的类 =属性（数据）+方法
类对象，简称为类，实例对象简称为实例
"""

class Person(object):
    age = 18

    def study(self):
        print("18岁上大学")

    def tanlianai(self):
        print("可以谈恋爱")


p = Person()
print(p.age)
p.study()
p.tanlianai()
