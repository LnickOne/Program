# coding:utf-8

import threading
import time


def foo():
    start = time.time()
    time.sleep(2)
    end = time.time()
    print threading.currentThread().getName(), "一共执行的的时间", end - start, '\n'


for i in range(5):
    t = threading.Thread(target=foo)
    t.start()
