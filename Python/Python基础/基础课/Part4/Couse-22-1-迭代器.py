# coding:utf-8

"""
迭代器是一个实现了迭代协议的容器对象

"""


class MyIterator(object):

    def __init__(self, step):

        self.step = step

    def __iter__(self):
        return self

    def next(self):
        if self.step == 0:
            raise (StopIteration)
        self.step -= 1
        return self.step


print(list(MyIterator(15)))

for item in MyIterator(13):
    print(item)
# p = MyIterator(3)
# print(p)
# print(p.next())
# print(p.next())
# print(p.next())
# print(p.next())
