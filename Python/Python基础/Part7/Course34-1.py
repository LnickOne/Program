# coding:utf-8

import threading


def worker():
    print "worker\n"


for i in range(5):
    t = threading.Thread(target=worker)  # threading是一个模块,有Thread这个类,类里面传一个构造函数
    t. start()
