#coding:utf-8

class queue(object):
	def __init__(self,queue):
		self.queue = queue


	def enqueue(self):
		self.queue.append(input("加入队列的元素是\n"))


	def dequeue(self):
		print ("最初的队列是",self.queue)
		print ("列表头部取出的元素是",self.queue.pop(0))
		print ("此时的队列是",self.queue)


que1 = queue([])
que1.enqueue()
que1.enqueue()
que1.dequeue()