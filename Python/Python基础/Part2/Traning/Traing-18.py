#coding:utf-8
#法1
dic1 = {'ip':'127.0.0.1','port':'8008'}
dic2={'user':'client','protocol':'TCP'}
dic3={}
dic3.update(dic1)
dic3.update(dic2)
print(dic3)


#法2
dic4={}
dic4=dic1.copy()
dic4.update(dic2)
print(dic4)

#法3
dic5={}
dic5=dict(dic1,**dic2)
print(dic5)

#法4
dic6={}
for key,value in dic1.items():
    dic6[key]=value
for m,n in dic2.items():
    dic6[m]=n
print(dic6)