#coding: utf-8

import random

print("craps掷骰子游戏开始")

N = random.randint(1,6)
n = random.randint(1,6)
k=N+n 
while True :
    if N + n ==  7 or N + n == 11:
        print("玩家赢，庄家输")
        break    
    if N + n ==  2 or N + n == 3 or N + n ==12:
        print("玩家输，庄家赢")
        break
    elif k == 4 or k ==5 or k ==6 or k ==8 or k ==9 or k==10 :
        print("掷出t点 ，请重新掷骰子")
        break


t= N+ n
print("t的大小是",t)
    
while 1 :    
    N = random.randint(1,6)
    n = random.randint(1,6)
    print("再次掷出的点数是",N+n)
    if N+n == t and N+n != 7:
        print ("点数为%d"%t)
        print("玩家赢，庄家输")
        break
    if N+n == 7:
        print ("点数为%d"%(N+n))
        print("玩家输，庄家赢")
        break
    else:
        print("无结果，重新投掷")
        continue

