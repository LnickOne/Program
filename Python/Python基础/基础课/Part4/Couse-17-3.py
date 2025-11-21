# coding:utf-8


class Person():
    """此类描述月光族如何省钱的方法"""

    def __init__(self, name, salary):
        self.name = name
        self.salary = salary

    def savemonny(self):
        print("每月定期存款工资的一半,{0}元".format(self.salary / 2.0))

    def consume(self):
       # print("消费在剩下的一半中支出")
        return self.salary / 2.0

    def consume_total(self):
        consume1 = 1000 #住房
        consume2 = 1200 #生活费
        if consume1 + consume2 > self.consume():
            print(self.name, "消费超标")
        else:
            print(self.name, "还可以进行其他消费")


foo = Person('李华', 20000)
foo.consume_total()
foo.savemonny()
