#coding:utf-8

class ArrayPattern(object):
    '定义数组模型类'
    
    def __init__(self, arrayList):
        self.arrayList = arrayList
        
    def shift(self):
        headItem = self.arrayList[0]
        print ('Item ', headItem, ' is deleted from the head of array.')
        self.arrayList = self.arrayList[1:]
        print ('The updated array is: ', self.arrayList, '\n')
        
    def unshift(self, headItem):
        tempList = [headItem]
        for item in self.arrayList:
            tempList.append(item)
        self.arrayList = tempList
        print ('Item ', headItem, ' is added on the head of array')
        print ('The updated array is: ', self.arrayList, '\n' ) 
       
    def push(self, endItem):
        self.arrayList.append(endItem)
        print ('Item ', endItem, ' is added on the end of array.')
        print ('The updated array is: ', self.arrayList, '\n'     )
    
    def pop(self):
        endItem = self.arrayList.pop()
        print ('Item ', endItem, ' is poped.')
        print ('The updated array is: ', self.arrayList, '\n'    )
          
            
a_array = ArrayPattern([1, 2, 3, 4, 5, 6, 7, 8])
a_array.shift()
a_array.unshift(9)
a_array.push(10)
a_array.pop()