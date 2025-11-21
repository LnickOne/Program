#coding:utf-8

"""
猜数字吧
guess number
"""
import random
import string

thenum = random.randint(0,100)
print (thenum)
while True :
    guess = input("请吧 输入一个数字:\n")
    if guess.isdigit():
        guess=int(guess)
        if guess == thenum :
            print("答对了！")
            break
        elif guess>thenum:
            print("猜大了哦")
        elif guess<thenum:
            print("猜小了啦" )
    else:
        print ("你输入字符了 ，请输入一个具体数字")
    