# coding:utf-8

"""
python多态演示,多态是指不同的对象有同一个方法,让不同的对象能调用同一个方法
"""


class People(object):
    def __init__(self, name):
        self.name = name

    def printName(self):
        print("In People类中,My name is %s", (self.name))


class Man(object):
    def __init__(self, name):
        self.name = name

    def printName(self):
        print("In People类中,My name is %s",(self.name))


for p in [People("AAA"), Man("BBB")]:
    p.printName()
