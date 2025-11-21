# coding:utf-8


#item 维护一个 物品仓库 添加进购物车的操作会调用
class Item(object):
    #为了每个实例的更改都能被保存，这个地方不能放在初始化里
    db = {'apple':3,'pear':3,'chocolate':4}

    def check(self,name):
        if self.db[name] != 0:
            return True
        else:
            return False

    def delete(self,name):  #确认仓库里的货物是否卖完
        if self.check(name) != 0:
            self.db[name] = self.db[name]-1
            return True
        else:
            print (name,'already sold out')
            return False

#cart中也有一个字典，用来维护每辆购物车中的物品
class Cart(object):
    def __init__(self,carname):
        self.carname = carname
        self.car  = {}

    def addthing(self,name):
        it = Item()
        if it.delete(name) == True:

            if name in self.car :
                self.car[name] = self.car[name]+1
            else:
                self.car[name] = 1


    def showthings(self):
        for i in self.car:
            print (i,self.car[i])

#用户用一个list来存储生成的car对象，之后就用list下标就可以访问到实例
class User(object):
    def __init__(self):
        self.index = 0
        self.carlist = []

    def addcar(self,carname):
        ca = Cart(carname)  #实例化购物车的货物,每个购物车都实例化之后放在列表里面
        self.carlist.append(ca) #在列表里面加入多个购物车

    def showcar(self):
        for i in self.carlist:
            print (i.carname)  #显示购物车的名字

    def addthing(self,name,carname):  #用户买东西,就是给购物车加货物
        for i in self.carlist:
            if i.carname == carname:
                i.addthing(name)  #调用购物车加货物的方法

    def showthing(self):  #显示购物车的货物
        for i in self.carlist:
            print (i.carname,'has things:')
            i.showthings() #调用购物车里显示货物的方法


#调用的逻辑 用户调用车，车添加物品就是调用物体库
if __name__ =='__main__':
    us = User()
    us.addcar('car1')
    us.addcar('car2')
    us.addthing('pear','car1')
    us.addthing('apple', 'car1')
    us.addthing('apple', 'car1')
    # us.addthing('apple', 'car1')
    # us.addthing('apple', 'car1')  #测试苹果是否卖完
    us.addthing('chocolate', 'car1')
    us.addthing('apple', 'car2')
    us.addthing('pear', 'car2')
    us.showthing()
