#coding:utf-8

class Foo(object):
	def __init__(self):
		print ("初始化")


	def __del__(self):
		#super (Foo,self).__del__ #调用父类的
		print("类消失")  #回收函数 ,就是用完了函数就自动执行回收函数

p1 =Foo()

list1 =[]

for item in range(10):
	list1.append(Foo())

for item in list1:
	print(item)
	print ("-----------------")

print ("-----------------")
print ("-----------------")
print ("-----------------")