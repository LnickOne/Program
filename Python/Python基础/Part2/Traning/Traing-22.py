#coding:utf-8

dict1={1:'a',2:'b',3:'c'}
dict2={4:'d',5:'e',6:'f'}
dict3={}
#修改为
#dict1={'d':'a','e':'b','f':'c'}
#dict2={4:'1',5:2,6:'3'}

list1=dict1.values()
list2=dict2.values()
dict3=dict(zip(list2,list1))
print(dict3)
  
        
list3=dict1.keys()
list4=dict2.keys()
dict4=dict(zip(list4,list3))
print(dict4)