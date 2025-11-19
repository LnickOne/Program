def score(num):
    num=int(num)
    if num>=90 and num<=100:
        print('A')
    elif num>=80 :
        print('B')
    elif num>=70 :
        print('C')
    elif num>=60:
        print('D')
    else:
        print('F')
        
if __name__=='__main__':
    n = input()
    print(score(n))