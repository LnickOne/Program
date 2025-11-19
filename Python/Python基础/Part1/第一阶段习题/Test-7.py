#coding: utf-8
def form(num):
    num = int (num)
    i = 1
    while i<=num: #num是行数,如果num是8
        j =num-i #动态获取数字前空格的个数,就是前面有8-1=7个空格          
        while j>0: #输出j个空格
            print(" ",end=' ')                    
            j-=1  #输出完空格后，开始输出*号
            
        z=i#输出左边
        while z>0:
            print("*",end=' ')
            z-=1
                
        k=2  #输出右边
        while k<=i:
            print("*",end =' ')
            k+=1
        print() #每次结束 输入一个回车键
        i+=1


if __name__=='__main__':
    n = input()
    form(n) 