# coding:utf-8

import math


class Point(object):
    def __init__(self, x1=0, y1=0, x2=0, y2=0):
        self.x1 = x1
        self.y1 = y1
        self.x2 = x2
        self.y2 = y2

    def __repr__(self):
        return ("((%d,%d)、(%d,%d))" % (self.x1, self.y1, self.x2, self.y2))

    # 勾股定理
    def length(self):
        return math.sqrt((self.x2 - self.x1)**2 + (self.y2 - self.y1) ** 2)

    # 斜率计算公式
    def slope(self):
        if self.x2 == self.x1:
            return "斜率None"

        return (self.y2 - self.y1) / (self.x2 - self.x1)


p = Point(5, 8, 2, 7)
print(p)
print(p.length())
print(p.slope())
