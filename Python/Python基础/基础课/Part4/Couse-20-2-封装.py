# coding:utf-8
"""
封装和隐藏,私有化  ,封装就是把属性和方法写在一起,把他们隐藏起来,留一些接口(方法)给别人调用
隐藏就是放到类里面

私有化就是通过两个下横线给变量弄成私有
"""

class Foo(object):
	def __init__ (self,x,y):
		self.__x = x
		self.y = y

	def __print_x_y(self):
		print (self.__x,self.y)

p = Foo(5,6)
# p.print_x_y()
# print (p.y)

# print (p._Foo__x) #通过这样把私有属性弄出来,python不是完全隐藏
p._Foo__print_x_y()





