# coding:utf-8


class StackQueue(object):
    """docstring for StackQueue"""

    def __init__(self, StackQueue):
        self.StackQueue = StackQueue

    def shift(self):
        print("返回并删除列表中的第一个元素\n", self.StackQueue.pop(0))

    def unshift(self):
        self.StackQueue.insert(0,input('在列表头部 "压入"一个新元素\n'))
        print(self.StackQueue)

    def push(self):
        self.StackQueue.insert(len(self.StackQueue),input("在列表尾部加上一个新元素\n"))
        print(self.StackQueue)


    def pop(self):
        print("返回并删除列表中的最后一个元素\n", self.StackQueue.pop())


StaQue = StackQueue([])
StaQue.unshift()
StaQue.unshift()
StaQue.unshift()
StaQue.unshift()

StaQue.shift()
StaQue.push()
StaQue.pop()
print("最后的列表为", StaQue.StackQueue)
