# coding:utf-8


class Stack(object):
    """docstring for Stack"""

    def __init__(self, stack):
        self.stack = stack

    def push(self):
        self.stack.append(input("输入加入栈的字符串\n").strip())

    def pop1(self):
        #print (FindDirPop())
        if FindDirPop():
            if len(self.stack) != 0:
                print("移除了", self.stack.pop())  # 这个pop使用了内建方法
                print ("该栈为",self.stack)
            else:
                print("该栈没有元素可以抛出")
        else:
            if len(self.stack) != 0:
                print(self.stack.pop(0), '被抛出')
                print ("该栈为",self.stack)
            else:
                print("该栈没有元素可以抛出")

    def isempty(self):
        if len(self.stack) == 0:
            return 1
        else:
            return 0

    def peek(self):
        if len(self.stack) != 0:
            print('peek取到堆栈的顶部数据项是',self.stack[0])

#检验pop的方法（函数）
def FindDirPop():
    re = False
    for i in dir(list):
        if i =='pop':
            re = True  # 表示内建pop 存在
            break
    return re




sta1 = Stack([])

sta1.push()
sta1.push()
sta1.push()
sta1.pop1()
print(sta1.isempty())
sta1.peek()
