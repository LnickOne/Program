# coding:utf-8


class MyTime(object):

    def __init__(self, timeValue, timeString):
        self.timeValue = timeValue
        self.timeString = timeString

    def update(self, timeValue, timeString):
        self.timeValue = timeValue
        self.timeString = timeString
        print('Time updated success.\n')

    def display(self, displaytype):

        day = self.timeValue.tm_mday
        if day <= 9:
            day2 = '0' + str(day)
        else:
            day2 = str(day)

        months = self.timeValue.tm_mon
        if months <= 9:
            months2 = '0' + str(months)
        else:
            months2 = str(months)

        year = self.timeValue.tm_year
        year2 = str(year)[2:]
        year4 = str(year)

        timeStringSplit = self.timeString.split()

        if displaytype == 'MDY':
            return months2 + '/' + day2 + '/' + year2
        elif displaytype == 'MDYY':
            return months2 + '/' + day2 + '/' + year4
        elif displaytype == 'DMYY':
            return day2 + '/' + months2 + '/' + year2
        elif displaytype == 'DMY':
            return day2 + '/' + months2 + '/' + year4
        elif displaytype == 'MODYY':
            return timeStringSplit[0] + ' ' + timeStringSplit[2] + ', ' + timeStringSplit[4]
        else:
            return self.timeString


import time
from time import sleep

timeValue = time.localtime(time.time())
timeString = time.ctime(time.time())
print('Current time and date is: ', timeString, '\n')
CurrentTime = MyTime(timeValue, timeString)

sleep(3)
timeValue = time.localtime(time.time())
timeString = time.ctime(time.time())
CurrentTime.update(timeValue, timeString)

print("'MDY'   -> MM/DD/YY ...... ", CurrentTime.display('MDY'))
print("'MDYY'  -> MM/DD/YYYY .... ", CurrentTime.display('MDYY'))
print("'DMY'   -> DD/MM/YY ...... ", CurrentTime.display('DMY'))
print("'DMYY'  -> DD/MM/YYYY .... ", CurrentTime.display('DMYY'))
print("'MODYY' -> Mon DD,YYYY ... ", CurrentTime.display('MODYY'))
print("Nothing Defined .......... ", CurrentTime.display('NothingDefined'))
