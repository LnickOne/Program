#coding:utf-8

#写一个函数实现以下功能
    #找出一个列表的中位数，列表的元素都是浮点数。
    #列表中的元素个数为奇数：比如L =[15.0, 5.3, 18.2], returns 15.0. 返回中位数
#   列表中的元素个数为偶数：比如L =[1.0, 2.0, 3.0, 4.0], returns 2.5. 返回中间2位数之和/2

def midian(m):
    if len(m) % 2 == 1 :
        i = 0
        while i < len(m):
            j = 0
            while j < len(m) - 1:
                if m[j] > m[j+1]:
                    m[j],m[j+1] = m[j+1],m[j]
                j+=1
            i+=1
    return m[int((len(m))/2)]
    
def midian1(m):    
    if len(m) % 2 == 0 :
        i = 0
        while i < len(m):
            j = 0
            while j < len(m) - 1:
                if m[j] > m[j+1]:
                    m[j],m[j+1] = m[j+1],m[j]
                j+=1
            i+=1
    return (  (m[int(len(m)/2 -1)]  +m[int(len(m)/2) ] ) /2 )



if __name__ == '__main__':
    list1 = [15.0, 5.3, 18.2]
    list2 = [1.0, 2.0, 3.0, 4.0]
    print(midian(list1))
    print(midian1(list2))