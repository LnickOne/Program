# coding:utf-8

import threading

"解决线程访问资源同步 用锁"

num = 0


def foo():
    global num
    num += 1
    print num, "\n"
for i in range(50):
    t = threading.Thread(target=foo)
    lock = threading.Lock()  # 上锁
    lock.acquire()
    t.start()
    lock.release()  # 释放锁
