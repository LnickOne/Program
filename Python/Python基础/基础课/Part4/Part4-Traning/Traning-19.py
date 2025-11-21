#coding:utf-8

#(a)
"""会陷入无限循环里面，因为重写了.keys方法， self.keys会首先调用子类的.keys方法，而子类的.keys方法中又调用了自己，形成了循环。这个地方必须申明调用父类的.keys方法才能取到键的值
#(b)
python2.7版本里，super方法是只能用于新类的，在继承标准类时使用会出错。使用dict.keys(）,即直接使用名字调用也会出错。 
。"""



class mydic(dict):
    def skeys(self):
    	#return sorted(self.values())		
    	return sorted(self.keys())


if __name__ =='__main__':
    mydic = mydic((('huang',2),('ge',32),('python',56)))
    print ('By itertor:'.ljust(13),[keys for keys in mydic])
    print ('By skeys:'.ljust(13),mydic.skeys())
