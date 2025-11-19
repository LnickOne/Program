# coding: utf-8
def num():
    numfind = []
    j = 0
    for i in range(100, 1000, 1):
        if i % 17 == 0:
            numfind.append(i)
            j += 1
    print ('能被17整除的三位数如下')
    for i in numfind:
        print(i)
    print ("一共有" + str(j) + "个")


if __name__ == '__main__':
    num()
