# coding:utf-8
"""

"""


class Foo(object):
    #pass

    def __init__(self,y):
        self.y= y


    def __getattribute__(self,attr): #拦截点属性的方法,不管有没有属性，照样拦截
        print("in __getattribute__")
        #return attr
        if attr == "y":
            return 30
        else:
            print("没有此属性") 

    def __getattr__(self,z):  #这家伙是没有属性才拦截  ， 这属性两个家伙都有，就执行__getattribute__ ，不执行__getattr__
        print ("in __getattr__")
        if z == "age":
            return 30   

            #按代码顺序出钩


p = Foo(7)
#p.z
print (p.y)
print (p.age)

#print(p.y)
#print (p.z)
#print(p.age) #模拟标准属性
#print (p.__dict__)
#print (dir(p))
# p.__setattr__('x',5)
# setattr (p,'y',25)
# print(p.x)
# print(p.y)
#print(p.__getattribute__('y'))
