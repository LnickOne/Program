#coding:utf-8
min=int(input('请输入时长 '))
def fmttime(minutes):
    HH=minutes/60
    MM=minutes%60
    print ('%d 分钟是 %d 小时 %d 分钟' %(minutes,HH,MM))
    
fmttime(min)