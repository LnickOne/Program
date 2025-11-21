# coding:utf-8


class RoundFloatManual(object):
    def __init__(self,val):
        assert isinstance(val,float),"数值必须是小数点类型"
        self.value = round(val,2)

    # def __str__(self):
    # 	return "the value %s" %(self.value)
    # 	#return str(self.value)

    #__repr__ = __str__

p = RoundFloatManual(7.56487)
#print(dir(p))
print (p)