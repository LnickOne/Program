#coding:utf-8

class Time60(object):
    def __init__(self,*rest):
        #输入的是这几种特殊的
        if len(rest) == 1:
            #这里rest已经是一个tuple类型
            if type(rest[0]) == tuple:
                self.hr = rest[0][0]
                self.min = rest[0][1]
            elif type(rest[0]) == dict:
                self.hr = rest[0]['hr']
                self.min = rest[0]['min']
            elif type(rest[0]) == str:
                index = rest[0].index(':')
                self.hr = int(rest[0][:index])
                self.min = int(rest[0][index+1:])
        #无输入
        elif len(rest) == 0:
            self.hr = 0
            self.min = 0
        #正常输入
        else:
            self.hr = rest[0]
            self.min = rest[1]
    def __str__(self):
        #2位，不足时以0占位
        return '%02d:%02d' % (self.hr,self.min)

    def __repr__(self):
        return repr('%02d:%02d' % (self.hr,self.min))

    def __add__(self, other):
        hr = self.hr + other.hr
        min = self.min + self.min

        if hr >=25:
            hr = hr -24

        if min >=60:
            min = min - 60
            hr = hr + 1
        return self.__class__(hr,min)

    def __iadd__(self, other):
        self.hr += other.hr
        self.min += other.min
        if self.min>=60:
            self.min = self.min -60
            self.hr =self.hr+1
        return self


if __name__ =='__main__':
    web = Time60(12,5)                          
    ti1 = Time60((10,20))
    ti2 = Time60({'hr':15,'min':40})
    ti3 = Time60('10:5')

    print (web)
    print (ti1)
    print (ti2)
    print (ti3)
    print (ti1+ti2)