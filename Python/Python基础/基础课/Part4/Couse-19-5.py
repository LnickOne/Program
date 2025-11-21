#coding:utf-8

class RoundFloat(float): #定义一个类，继承父类（python内定义的 float）
	def __new__(cls,val): #定义一个__new__方法 覆盖父类(float)__new__方法
		return float.__new__(cls,round(val,6))
#这个cls 呢，指的是类RoundFloat, 参数是round(val,6) ,这样生成数值的时候就传进去咯
#这样写，是因为不可变类型(int float 字符串) 这种不能用__init__初始化
p = RoundFloat(2.45232323256)
print(p)