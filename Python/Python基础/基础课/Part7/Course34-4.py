# coding:utf-8

"""
类传实例 
创建一个类是Thread的子类,创建这个子类的实例
"""
from threading import Thread
import time
import urllib2


class GetUrlThread(Thread):  # 把线程类当做父类

    def __init__(self, url):
        self.url = url
        super(GetUrlThread, self).__init__()  # 从父类继承一个构造函数的方法  相当于Thread.__init__(self)
        # Thread.__init__(self)

    def run(self):  # 把父类的run方法覆盖
        resp = urllib2.urlopen(self.url)
        print self.url, resp.read()


def get_responses():
    urls = ['http://www.jd.com', 'http://taobao.com']
    start = time.time()
    threads = []
    for url in urls:
        t = GetUrlThread(url)
        threads.append(t)
        t.start()
    # for t in threads:
    #     t.join() #阻塞
    print "Elapsed time:%s" % (time.time() - start)
get_responses()
