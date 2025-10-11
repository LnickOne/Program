#coding:utf-8
import random  

def leapyear(year):
    if year<1900 or year>2016:
        print ('year error')
    elif (year%4==0 and year%100!=0) or (year%4 == 0 and year%400==0):
        return year
years=[]
for i in range(10):
    years.append(random.randint(1900,2016))
print("随机抽取的年份有", years)
print ("过滤后得到的闰年有",list(filter(leapyear,years)))


#列表解析的形式
print ([n for n in [random.randint(1900,2016) for i in range(10)] if ((n%4==0 and n%100!=0) or (n%4==0 and n%100==0))])
