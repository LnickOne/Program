#coding:utf-8
#(a)小题

max2 = lambda x,y : x if x>y else y
min2 = lambda x,y : x if x<y else y

print (max2 (4,8))
print (min2 (4,8))
 

#(b)小题

def my_max(*parameter):
    reconsitution = parameter[0]
    for i in parameter:
        reconsitution = max2(reconsitution,i)
    return reconsitution

def my_min(*parameter):
    reconsitution = parameter[0]
    for i in parameter:
        reconsitution = min2(reconsitution,i)
    return reconsitution

print (my_max(1,9,6))
print (my_max('saq','sasq','zzzz'))
print (my_min(1,9,6))
print (my_min('saq','sasq','zzzz'))