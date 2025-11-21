#coding:utf-8
def tax(rate=0.2):
    price=float(input('请输入价格 '))
    print ('你的税费是 %.2f' %round(price*rate,2))
 
tax()