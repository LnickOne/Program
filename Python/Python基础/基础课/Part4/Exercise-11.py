# coding:utf-8


class User(object):
    """管理顾客,顾客可以有多个购物车"""

    def __init__(self):
        self.cartlist = []

    # 增加购物车
    def AddBuycart(self, CartName):
        cart = Cart(CartName)
        self.cartlist.append(cart)


    # 用户用购物车买东西
    def BuyItem(self, CartName, ItemName):
        for BuyCart in self.cartlist:
            if BuyCart.CartName == CartName:
                BuyCart.AddCartItem(ItemName)

    # 显示用户的购物车
    def ShowUserBuyCart(self):
        for i in self.cartlist:
            print(i.CartName, "这个购物车有以下货物")
            i.ShowCartItem()


class Item(object):
    """管理库存"""
    Item = ['Apple', 'Banana', 'lemon']
    Num = [2, 3, 4]
    ItemDB = dict(zip(Item, Num))

    def __init__(self):
        pass

    # 当库存的货物加入购物车后相对应地减少库存
    def DelItem(self, Name):

        if self.ItemDB[Name] != 0:
            self.ItemDB[Name] = self.ItemDB[Name] - 1
            return True
        else:
            print(Name, "卖完")
            return False


class Cart(object):
    """管理购物车，购物车可以放多个货物，包括多个同样的货物"""

    def __init__(self, CartName):
        self.CartName = CartName  # 存实例购物车的名字
        self.cart = {}  # 这个实例属性用来存储购物车里面的货物名称和货物个数

    # 购物车增加货物
    def AddCartItem(self, ItemName):
        it = Item()
        if it.DelItem(ItemName) == True:
            
            if ItemName in self.cart:
                self.cart[ItemName] = self.cart[ItemName] + \
                    1  # 如果购物车里面有这个货物了，就增加1
            else:
                self.cart[ItemName] = 1  # 这个购物车没有货物的话 就置为1

    # 显示购物车的货物
    def ShowCartItem(self):
        for Item in self.cart:
            print(Item, self.cart[Item])


user = User()
user.AddBuycart('cart1')
user.AddBuycart('cart2')
user.BuyItem('cart1', 'lemon')
user.BuyItem('cart1', 'lemon')
user.BuyItem('cart1', 'lemon')
user.BuyItem('cart1', 'lemon')
user.BuyItem('cart1', 'lemon')
user.BuyItem('cart2', 'Apple')

it = Item()
print(it.ItemDB)

user.ShowUserBuyCart()
