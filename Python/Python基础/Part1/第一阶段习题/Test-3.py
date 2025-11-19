#coding:utf-8
def sum(num):
    num=int(num)
    i=1
    while i<=num:
        i=i+1    
        j=1
        total=0
        while j<i:       #内层循环 ,看作是外层循环一共有5条语句，一条条执行
            total=total+j            
            if j<i-1:
                print(str(j)+ "+",end =' ')     #将格式弄好         
            if j==i-1:
                print(str(j),end =' ')           
            j=j+1
        print("=",total) #外层循环 ,在这里输出total的值后，回到while进行第二次判断


if __name__=='__main__':
    print("输入值")
    n = input()
    sum(n) 