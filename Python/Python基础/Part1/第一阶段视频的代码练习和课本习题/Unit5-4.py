# coding:utf-8
def year(num):
    num = int(num)
    if (num % 4 ==0 and num %100!=0) or (num % 400 ==0 and num% 4 ==0):
       print (num,"这是闰年" )
    else:
        print(num,"这不是闰年")

if __name__=='__main__':
    n = input()
    print(year(n))