# coding:utf-8

import threading


def worker(num):
    print "worker" + str(num)

threads = []

for i in range(5):
    t = threading.Thread(target=worker, args=(10,))  # threading是一个模块,有Thread这个类,类里面传一个构造函数
    threads.append(t)
for t in threads:
    t. start()
