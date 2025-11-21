# coding:utf-8


class Foo(object):

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def test(self):
        print("in 父类Foo里面")


class Foo2(Foo):  # 括号里面写父类
    def __init__(self,x,y,z):
        print("调用子类Foo2自己的构造函数")
        #Foo.__init__(self,x,y)   #这里是调用父类的__init__ (注这个不是构造函数，就当做是普通的函数就行，他就有实例属性用了)
        super (Foo2,self).__init__(x,y)   #语法 super(子类,self)  ,这个也是调用父类__init__的方式  
        self.z = z


    def test(self):
        print(self.x,self.y)
        print("in 子类Foo2")
        #Foo.test(self) = super (Foo2,self).test() 这个等式成立

p = Foo2(4,5,6)
print ("-------------")
p.test()
# print(Foo2.__bases__)
# print (issubclass(Foo2,Foo))