# coding:utf-8

num = 6
i = 1
while i <= num:
    i += 1;j = 1
    total = 0
    while j < i:
        total = total + j
        if j <i-1:
            print(str(j) + "+", end=" ")
        elif j ==i - 1:
            print(str(j),end=" ")
        j += 1
    print("=" + str(total))
