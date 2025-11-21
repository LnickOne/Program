#coding-utf-8


'''几何. 创建一个直线/直线段类。 除主要的数据属性： 一对坐标值(参见上一个练习)外，
它还具有长度和斜线属性。你需要覆盖__repr__()方法(如果需要的话，还有__str__()方法)，
使得代表那条直线(或直线段)的字符串表示形式是由一对元组构成的元组，即，((x1, y1),
(x2, y2)).
总结：
__repr__ 将直线的两个端点(始点和止点)显示成一对元组
length 返回直线段的长度 - 不要使用"len", 因为这样使人误解它是整数。
slope 返回此直线段的斜率(或在适当的时候返回 None)'''
 
from math import sqrt
 
class Line(object):
    def __init__(self, x1=0, y1=0, x2=0, y2=0):
        self.x1 = x1
        self.x2 = x2
        self.y1 = y1
        self.y2 = y2
        self.length = 0
        self.slope = 0
 
    def getLength(self):
        self.length = sqrt((self.x2-self.x1)**2 + (self.y2-self.y1)**2) 
        return self.length
 
    def getSlope(self):
        if self.length == 0:
            self.slope = None
        if (self.x2 == self.x1) or (self.y2 == self.y1):
            self.slope = None
        else:
            self.slope = (self.y2-self.y1)/(self.x2-self.x1) #斜率计算公式
        return self.slope
 
    def __str__(self):
        return "((%d,%d),(%d,%d))" % (self.x1, self.y1, self.x2, self.y2)
 
    __repr__ = __str__
 
if __name__=='__main__':
    L = Line(2,2,4,6)
    print(L)
    print('length is: %f' % L.getLength())
    print('slope is: ' , L.getSlope())