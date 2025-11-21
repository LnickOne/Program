#coding:utf-8

import time
from time import sleep
class Time(object):
	def __init__(self,timeValue,timeString):
		self.timeValue = timeValue
		self.timeString = timeString

	def update(self,timeValue,timeString):
		self.timeValue = timeValue
		self.timeString = timeString

		print ("时间更改成功")

	def display(self,display):

		#日
		day = self.timeValue.tm_mday

		if day <10:
			day = '0' + str(day)
		else:
			day = str(day)

		#月
		Month = self.timeValue.tm_mon
		
		if Month <10:
			Month = '0' + str(Month)
		else:
			Month = str(Month)

		#年

		year = self.timeValue.tm_year
		year = str(year)
		year2 = year[2:]
		year4 = str(year)

		if display == 'MDY':
			return Month + '/' + day +'/' + year2
		elif display =='MDYY':
			return Month + '/' + day + '/' + year4

		elif display =='DMY':
		
			return day + '/' + Month +'/' + year2
		elif display =='DMYY':
			return day + '/' + Month +'/' + year4
		
		elif display =='MODYY':	
			return timeString.split()[0] + ' ' + timeString.split()[2] +',' + year4

		else :
			return self.timeString


timeValue = time.localtime()
timeString = time.ctime()

# print (timeValue)
# print (timeString)

#实例化

MyTime = Time (timeValue,timeString)

print (MyTime.display('MDY'))
print (MyTime.display('MDYY'))
print (MyTime.display('DMY'))
print (MyTime.display('DMYY'))
print (MyTime.display('MODYY'))
print (MyTime.display('测试'))


sleep (4)
MyTime.update(time.localtime(time.time() ),time.ctime(time.time() ))


print (MyTime.display('MDY'))
print (MyTime.display('MDYY'))
print (MyTime.display('DMY'))
print (MyTime.display('DMYY'))
print (MyTime.display('MODYY'))
print (MyTime.display('测试'))