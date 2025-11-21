#coding:utf-8

class StackPattern(object):
    '定义堆栈模型类'
    
    def __init__(self, stackList):
        self.stackList = stackList
        
    def push(self, topItem):
        self.stackList.append(topItem)
        print ('Item ', topItem, ' is pushed on the top of Stack.')
        print ('The updated Stack is: ', self.stackList, '\n')
    
    def popvalue(self):
        if findPop() == True:
            topItem = self.stackList.pop()
            print ('Item ', topItem, ' has been poped.')
            print ('The updated Stack is: ', self.stackList, '\n')
        else:
            topItem = self.stackList.pop[-1]
            print ('Item ', topItem, ' has been poped.')
            self.stackList = self.stackList[:-2]
            print ('The updated Stack is: ', self.stackList, '\n')
        
    def isempty(self):
        if len(self.stackList) == 0: 
        	return True
        else: 
        	return False
        
    def peek(self):
        return self.stackList[-1]
    

def findPop():
    result = False
    for item in dir(list):
        if item == 'pop':
            result = True
            break
    return result
            
a_stack = StackPattern([1, 2, 3, 4, 5, 6, 7, 8])
a_stack.push(9)
a_stack.popvalue()
print ('Is Empty Value: ', a_stack.isempty())
print ('Peek value', a_stack.peek())