
#coding:utf-8
class Foo(tuple): #继承元组父类
    
    def __new__(cls, c,d):
        return super(Foo, cls).__new__(cls,[c,d])

    def __init__(self,c,d):
        super(Foo, self).__init__()



if __name__ == '__main__':
    foo = Foo(*{'c':1,'d':2})
    #f1 = Foo(1,'sasasj')
    #print (f1)
    #print(f1.a)
    print (foo)


