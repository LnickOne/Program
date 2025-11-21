#coding:utf-8

class Point(object):
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y
 
    def __str__(self):
        return '(%d,%d)' % (self.x, self.y)
 
 
if __name__=="__main__":
    p = Point()
    print(p)
    print("p的x坐标：%d" % p.x)
    print("p的y坐标：%d" % p.y)