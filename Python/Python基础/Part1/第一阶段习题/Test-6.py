#coding: utf-8
def form(num):
    num = int (num)
    i = 1
    while i<=num:
        j =num-i #动态获取数字前空格的个数              
        while j>0: #输出j个空格
            print(" ",end=' ')                    
            j-=1
            
        z=i#输出左边
        while z>0:
            print(z,end=' ')
            z-=1
                
        k=2 #输出右边
        while k<=i:
            print(k,end =' ')
            k+=1
        print()
        i+=1


if __name__=='__main__':
    print('输入值')
    n = input()
    form(n) 