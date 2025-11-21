#coding:utf-8

def countToFour1() :
    for eachNum in range(5):
        print (eachNum)

def conuntToFour2(n) :
    n = int (n)
    for eachNum in range(n,5):
        print (eachNum)

def countToFour3(n =1):
    n = int (n)
    for eachNum in range(n,5):
        print (eachNum)
        
if __name__ == '__main__':
    n = input()
    countToFour1()
    conuntToFour2(n)
    countToFour3(n =1)
#答 ：      countToFour1    countToFour2    countToFour3
#input2       0-4             2-4               1-4
#input4       0-4             4                 1-4
#input5       0-4             None              1-4
