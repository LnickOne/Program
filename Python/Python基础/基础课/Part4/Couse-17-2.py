# coding:utf-8

"""
此类是抽取日志文件中的ip地址的工具
"""


class FindIp(object):

    def __init__(self, path):
        self.txtfile = path

    def chou_sogou_ip(self):
        file1 = open(self.txtfile, "r")
        iplist =[]
        for line in file1:
            s = line.find('"Sogou web spider/4.0')
            if s > 0:
                iplist.append(line[:s].strip())
        file1.close()
        return iplist

    def chou_sogou_ip2(self):
        file1 = open(self.txtfile, "r")
        iplist = file1.readlines()  #file1文件里的内容全写入一个大列表里面
        #print (iplist)
        outlist = []
        for item in iplist:
            s = item.find('"Sogou web spider/4.0')
            if s > 0:
                outlist.append(item[:s].strip())
        file1.close()
        return outlist

p = FindIp("ip.txt")
# sougouip =p.chou_sogou_ip()
# print(list(set(sougouip)))
sgip =p.chou_sogou_ip2()
print (list(set(sgip)))