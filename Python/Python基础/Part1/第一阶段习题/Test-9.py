#coding: utf-8
def mix(num):
    num = int (num)
    i=1
    while i<=num:
        i+=1
        j=1
        total=0
        k=""
        r=1
        while r <i:
            k=k+str(r)
            r+=1        
        while j<i: 
            print(j,end=' ')
            if j==i-1:
                print("*"+str(num-1)+"+"+str(j),end=' ')                             
            k=int (k)
            total=k*(num-1)+j
            j+=1
        print("=",total)


if __name__ == '__main__':
    n = input()
    mix(n)

