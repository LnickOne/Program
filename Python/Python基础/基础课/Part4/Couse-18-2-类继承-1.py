#coding:utf-8

class Foo(object):
	pass

class Foo2(Foo): #括号里面写父类
	pass

print(issubclass(Foo2,Foo))