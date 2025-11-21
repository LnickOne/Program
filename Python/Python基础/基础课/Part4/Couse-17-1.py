# coding:utf-8
"""

"""


class TestClass(object):
    """测试类属性和实例属性"""
    jishu = 100
    my_list = []

    def testJishu(self, number):
        """定义实例属性"""
        self.jishu = number

    def print_jishu(self):
        print("jishu,我是实例变量:", self.jishu)


mytest = TestClass()
#print (dir(mytest))
mytest.testJishu(20)
# mytest.print_jishu()

# 用实例对象调用类的属性jishu,隐藏类的这个属性,在这里对该变量的修改,不会影响到类属性(变量)的值
# 但是如果类属性是可改变的类型,就可以通过实例调用修改.

mytest.jishu += 1
mytest.my_list.append("change by new object")

# print(mytest.jishu)  # 调用的是类属性jishu
# print(mytest.my_list)
# print(TestClass.jishu) #这是不可修改的类型
# print(TestClass.my_list)#这是可变修改的类型

TestClass.jishu +=1
TestClass.my_list.append("change my object2")
print(mytest.jishu)
print(TestClass.jishu)
print(TestClass.my_list)


