#coding:utf-8


class QueuePattern(object):
    '定义队列模型类'
    
    def __init__(self, queueList):
        self.queueList = queueList
        
    def enqueue(self, endItem):
        self.queueList.append(endItem)
        print ('Item ', endItem, ' is added at the end of Queue.')
        print ('The updated Queue is: ', self.queueList, '\n')
    
    def dequeue(self):
        headItem = self.queueList[0]
        print ('头部Item ', headItem, ' has been deleted.')
        self.queueList = self.queueList[1:]
        print ('The updated Queue is: ', self.queueList, '\n')
        
            
a_queue = QueuePattern([1, 2, 3, 4, 5, 6, 7, 8])
a_queue.enqueue(15785)
a_queue.dequeue()
