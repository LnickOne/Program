#coding:utf-8

#类绑定
class Foo(object):
	def test(self): #实例方法,第一个参数为self
		print("In test()")
		#print(self)
	@staticmethod   
	def foo(x):#静态方法 ,第一个参数传的是变量，不带self,语法上报错后就在上面给staticmethod
		print ("in foo()" + x)

	#foo = staticmethod (foo)

	@classmethod  #类方法,第一个参数必须传类，有了classmethod 第一个参数就和self 不同了
	def foo2(abc,y):
		print ("in foo2"+y)
		print (abc)
	#foo2 = classmethod(foo2)


p = Foo()  #绑定之后才能调用方法
p.test()

Foo().test()

p.foo("hello")  
Foo.foo ("python")
p.foo2("test class")
Foo.foo2("test in Foo")