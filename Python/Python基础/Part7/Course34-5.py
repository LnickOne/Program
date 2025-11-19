# coding:utf-8

"""
守护线程
守护线程的意思是,主进程和其他不用等守护线程退出,只要他们退出
"""
import threading
import time


def First():
    print threading.currentThread().getName() + ' ' + "starting\n"
    time.sleep(2)
    print threading.currentThread().getName() + ' ' + "Exiting\n"


def Second():
    print threading.currentThread().getName() + ' ' + "starting\n"
    print threading.currentThread().getName() + ' ' + "Exiting\n"

d = threading.Thread(name='First', target=First)
t = threading.Thread(name='Second', target=Second)

d.setDaemon(True)  # 守护线程表示我这个线程不重要
d.start()
d.join(4)  # 阻塞,没设置参数就是说我本线程没执行完你其他线程不能执行,设置参数就是等多少秒你其他进程就能执行了
t.start()
