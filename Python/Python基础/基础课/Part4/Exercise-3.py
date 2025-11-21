# coding:utf-8

# 第一问，基本任务


def dollarize(dollar):
    dollar1 = dollar  # 把初始值给一个变量，后面判断正负用

    dollar = round(dollar, 2)
    dollar = str(dollar)
    if float(dollar) < 0:  # 先把 -号 剥离
        dollar = str(round(float(dollar), 2)).split('-')[1]

    FoloatLeft = dollar.split('.')[0]
    FoloatRight = dollar.split('.')[1]

    while len(FoloatRight) < 2:  # 检测小数点后面的位数起码有两位
        FoloatRight = FoloatRight + str('0')

    dollar = dollar.split('.')[0] + "." + FoloatRight

    dollar = list(dollar)
    # print(dollar)

    # 插入逗号
    i = 6
    j = 0
    while len(dollar) > i:

        dollar.insert(-i - j, ',')
        i += 3
        j += 1
        if ',' in dollar:
            dollar.remove(',')

    # if dollar[0] == ',':
    #     dollar.remove(',')
    # print(dollar)
    if float(dollar1) > 0:
        dollar = '$' + ''.join(dollar)
    else:
        dollar = '-' + '$' + ''.join(dollar)
    # dollar=''.join(dollar)
    print(dollar)


dollarize(-1234567.8901)


# 写类和（a）,(b),(c) 小题

class MoneyFmt(object):
    def __init__(self, dollar):
        self.dollar = float (dollar)

    #(a) 小题
    def update(self, NewDollar):
        self.dollar = NewDollar
    #(c) 小题
    def __bool__(self):
        print ("I am __nonzero__")
        if float (self.dollar) < 1:
            return False
        else :
            return True


    def __repr__(self):
        return self.dollar

    #(b)小题
    def __str__(self):
        dollar1 = self.dollar  # 把初始值给一个变量，后面判断正负用

        self.dollar = round(self.dollar, 2)
        self.dollar = str(self.dollar)
        if float(self.dollar) < 0:  # 先把 -号 剥离
            self.dollar = str(round(float(self.dollar), 2)).split('-')[1]

        FoloatLeft = self.dollar.split('.')[0]
        FoloatRight = self.dollar.split('.')[1]

        while len(FoloatRight) < 2:  # 检测小数点后面的位数起码有两位
            FoloatRight = FoloatRight + str('0')

        dollar = self.dollar.split('.')[0] + "." + FoloatRight
        dollar = list(dollar)

        # 插入逗号
        i = 6
        j = 0
        while len(dollar) > i:

            dollar.insert(-i - j, ',')
            i += 3
            j += 1
            if dollar[0] == ',':
                dollar.remove(',')

        if float(dollar1) > 0:
            dollar = '$' + ''.join(dollar)
        else:
            dollar = '-' + '$' + ''.join(dollar)

        return (dollar)
        #print (dollar)


p = MoneyFmt(-1234567.8901)
#p.__str__()   p是print 的情况，用括号调用即可
print (p)
p.update(234543245.36)
print (p)


#以下测试(c) 小题
p.update(0.5)
print (p)
print (bool(p))
