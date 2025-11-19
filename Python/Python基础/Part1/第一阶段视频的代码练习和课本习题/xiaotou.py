#coding:utf-8
"""
a说我不是小偷
b说c是小偷
c说小偷是d
d说c说假话
"""
for xiaotou in ['a','b','c','d']:
    sum =(xiaotou !='a')+(xiaotou == 'c') + (xiaotou =='d')+(xiaotou!='d')
    if sum == 3:
        print ("小偷是%s" %xiaotou)