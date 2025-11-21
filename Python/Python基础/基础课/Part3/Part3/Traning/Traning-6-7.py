#coding:utf-8

def connect(list1,list2):
    if len(list1) != len(list2):
        print ('两个列表长度必须相等')
    else:
        print (list(map(lambda i:i,list1))) 
        
        print (list(zip(list1,list2)))
 
connect([1,2,3],['abc','def','ghi'])
