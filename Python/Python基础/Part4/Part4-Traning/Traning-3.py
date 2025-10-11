# coding:utf-8


# 基本任务:dollarize()函数
def dollarize(n):
    n = float(n)
    fl = str(round(n, 2))

    if n < 0:
        fl = str(round(n, 2)).split('-')[1]

    dec = fl.split('.')[1]  # 小数点右半部分
    while len(dec) < 2:
        dec = dec + '0'
    fl2 = fl.split('.')[0] + '.' + dec  # 小数点左半部分
    fl2 = list(fl2)
    lens = len(fl2)
    i, j = 6, 0
    while lens > i:
        fl2.insert(-i - j, ',')
        i += 3
        j += 1
    if n < 0:
        if n is not '-':
            n = '<->'
        return n + '$' + ''.join(fl2)
    else:
        return '$' + ''.join(fl2)


n = input("输入你要修改的浮点数\n")
print(dollarize(n))


class MoneyFmt(object):
    '''把函数dollarize转换为一个类，并且包含以下的五个方法'''

    def __init__(self, value=0.0, default='-'):
        self.value = float(value)
        self.default = default  # 将负号赋值给实例

    #(a)小题,实现数据值修改功能
    def update(self, newvalue=None):
        if newvalue is not None :
            self.value = newvalue

    def __repr__(self):
        return repr(self.value)

    #(b)小题
    def __str__(self):
        try:
            fl = str(round(self.value, 2))
            if self.value < 0:
                fl = str(round(self.value, 2)).split('-')[1]
            dec = fl.split('.')[1]
            while len(dec) < 2:
                dec = dec + '0'
            fl2 = fl.split('.')[0] + '.' + dec
            fl2 = list(fl2)
            lens = len(fl2)
            i, j = 6, 0
            while lens > i:
                fl2.insert(-i - j, ',')
                i += 3
                j += 1
            if self.value < 0:
                if self.default is not '-':
                    self.default = '<->'
                return self.default + '$' + ''.join(fl2)
            else:
                return '$' + ''.join(fl2)

        except (TypeError, ValueError):
            return 'Input should be a number'
        
    #(c)小题
    def __nonzero__(self):
        if self.value == 0:
            return False
        else:
            return True


moneyfmt = MoneyFmt(1234567.8901)
print(moneyfmt)

moneyfmt.update(156456121.2454)
print (moneyfmt)