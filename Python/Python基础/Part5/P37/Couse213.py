# coding:utf-8
"""
重载操作符-----+ 可以让2个数相加 还可以连接两个字符串
模拟标准类型
"""


class Time60(object):
    def __init__(self,hr,min):
        self.hr = hr
        self.min = min

    def __str__(self):
        return ("%d:%d" %(self.hr,self.min))

    def __add__(self,other):
        return self.__class__(self.hr + other.hr,self.min + other.min)
        return Time60(self.hr + other.hr,self.min + other.min)


mon = Time60(10,30)
tue = Time60(11,15)
print (mon+tue)