# coding:utf-8

import threading
import urllib2
"解决线程访问资源同步 用锁"


class FetchUrls(threading.Thread):
    """
    Thread checking URLs.
    """

    def __init__(self, urls, output, lock):
        threading.Thread.__init__(self)
        self.urls = urls
        self.output = output
        self.lock = lock

    def run(self):
        """
                Thread run method .Check URLs one by one
        """
        while self.urls:
            url = self.urls.pop()
            req = urllib2.Request(url)
            try:
                d = urllib2.urlopen(req).read()
            except urllib2.URLError, e:
                print 'URL %s failed:%s' % (url, e.reason)
            self.lock.acquire()
            self.output.write(d)
            self.lock.release()
            print 'write done by %s' % self.name
            print 'URL %s fetched by%s' % (url, self.name)


def main():
    urls1 = ['http://www.baidu.com', 'http://www.jd.com']
    urls2 = ['http://www.taobao.com', 'http://wwww.126.com']
    lock = threading.Lock()
    f1 = open('output.txt', 'w+')
    t1 = FetchUrls(urls1, f1, lock)
    t2 = FetchUrls(urls2, f1, lock)
    t1.start()
    t2.start()
    t1.join()
    t2.join()
    f1.close()

if __name__ == '__main__':
    main()


# num = 0
# def foo():
#     global num
#     num += 1
#     print num, "\n"
# for i in range(50):
#     t = threading.Thread(target=foo)
#     lock = threading.Lock()  # 上锁
#     lock.acquire()
#     t.start()
#     lock.release()  # 释放锁
