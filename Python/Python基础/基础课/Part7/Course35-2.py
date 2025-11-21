# coding:utf-8

import threading
import time


class Foo(threading.Thread):

    def run(self):
        print threading.currentThread().getName(), "开始", '\n'

        print threading.currentThread().getName(), "结束", '\n'


def foo():
    print threading.currentThread().getName(), "开始", '\n'
    time.sleep(2)
    print threading.currentThread().getName(), "结束", '\n'

t = Foo()
d = threading.Thread(target=foo)
t.start()
d.setDaemon(True)
d.start()
d.join(3)

# for i in range(5):
#     t = Foo()
#     t.start()
