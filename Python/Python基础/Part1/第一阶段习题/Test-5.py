#coding: utf-8
def example1(num):
    print('样式1')
    num = int (num)
    i = 1
    while i<=num:
        i +=1
        j =1
        while j<i:            
            print(j,end = ' ')
            j+=1
        print()
        
def example2():
    print ('样式2')
    num=6
    i=1
    while i<=num:
        print(i,end= ' ')
        i+=1
    print()
    
    num=5
    i=1
    while i<=num:
        print(i,end= ' ')
        i+=1
    print()
    
    num=4
    i=1
    while i<=num:
        print(i,end= ' ')
        i+=1
    print() 
    
    num=3
    i=1
    while i<=num:
        print(i,end= ' ')
        i+=1
    print()    
    
    num=2
    i=1
    while i<=num:
        print(i,end= ' ')
        i+=1
    print()    
    
    num=1
    i=1
    while i<=num:
        print(i,end= ' ')
        i+=1
    print()    


def example3():
    print("样式3")
    num=6  #num 即为行数
    i=1
    while i<=num:
        j =num-i #动态获取数字前空格的个数              
        while j>0: #输出j个空格
            print(" ",end=' ')                    
            j-=1
            
        z=i#输出左边
        while z>0:
            print(z,end=' ')
            z-=1
        print()
        i+=1
if __name__ =='__main__':
    n= input ()
    example1(n)
    example2()
    example3()