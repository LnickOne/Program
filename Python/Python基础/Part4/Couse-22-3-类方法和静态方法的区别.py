# coding:utf-8


"""
类方法和静态方法的区别
"""
import time


class Date(object):
    def __init__(self, year, month, day):
        self.year = year
        self.month = month
        self.day = day

    #静态方法，返回的是实例，所以print会打出内存地址
    # @staticmethod
    # def now():
    #     t = time.localtime()
    #     return Date(t.tm_year, t.tm_mon, t.tm_mday)

    # @staticmethod
    # def tomorrow():
    #     t = time.localtime(time.time() + 86400)
    #     return Date(t.tm_year, t.tm_mon, t.tm_mday)


    #类方法 ,返回的是类
    @classmethod
    def now(cls):
        t = time.localtime()
        return cls(t.tm_year, t.tm_mon, t.tm_mday)
    @classmethod
    def tomorrow(cls):
        t = time.localtime(time.time()+ 86400)
        return cls(t.tm_year, t.tm_mon, t.tm_mday)

class EuroDate(Date):
    def __str__(self):
        return ("%02d/%02d/%04d") % (self.day, self.month, self.year)


print(EuroDate.now().year)
print(EuroDate.tomorrow())


# a = Date(1967,4)
# b = Date.now()
# c = Date.tomorrow()
# print (b.year,b.month)
# print (c)
