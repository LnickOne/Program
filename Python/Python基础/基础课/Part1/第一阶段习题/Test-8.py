#coding: utf-8
def form(num):
    num = int (num)
    i = 1
#输出上半部分
    while i<=num: #num是行数
        j =num-i #动态获取数字前空格的个数              
        while j>0: #输出j个空格
            print(" ",end=' ')                    
            j-=1
            
        z=i#输出左边
        while z>0:
            print("*",end=' ')
            z-=1
                
        k=i  #输出右边
        while k>1:
            print("*",end =' ')
            k=k-1
        print()
        i+=1 #循环结束条件
#输出下半部分
    i=1
    while i<num:
        j =i             
        while j>0: #输出j个空格
            print(" ",end=' ')                    
            j-=1
        
        z=num   #输出左边
        while z>i:
            print("*",end=' ')
            z-=1            
        
        k=num-i  #输出右边,右边有num-i个星星
        while k>1:
            print("*",end =' ')
            k-=1
        print()
        i+=1#循环结束条件


if __name__ == '__main__':
    n =input()
    form(n)