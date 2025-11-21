# coding:utf-8
import time
import threading
import re
f = open("test").read()


def frequency(str, f, option=True):
    start = time.clock()
    str_re = re.compile(str)
    number = len(str_re.findall(f))
    end = time.clock()
    if option:
        print "单线程消费时间", end - start

    return number

print frequency(r"\w", f)


def MyThread(str, f,  dgree=10):
    start = time.clock()
    f_list = f.split("\n",  dgree)
    threads = []
    for i, j in enumerate(f_list):
        t = threading.Thread(target=frequency, args=(str, j, False))
        threads.append(t)
    for i in range(len(f_list)):
        threads[i].start()
    for i in range(len(f_list)):
        threads[i].join()
    end = time.clock()
    print "多线程消费时间", end - start

MyThread(r"\w", f)
