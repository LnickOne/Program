# coding:utf-8
import Queue
import threading
import urllib2
import re


class Foo(threading.Thread):

    def __init__(self, queue, out_queue):
        threading.Thread.__init__(self)
        self.queue = queue
        self.out_queue = out_queue

    def run(self):
        while True:
            url = self.queue.get()
            for item in self.download_url(url):
                out_queue.put(item)
            self.queue.task_done()

    def download_url(self, url):
        html = urllib2.urlopen(url).read()
        url_href = re.findall(r'href=\"(.+?)\"', html)
        return url_href


class Consumer(threading.Thread):

    def __init__(self, out_queue):
        threading.Thread.__init__(self)
        self.out_queue = out_queue

    def run(self):
        while True:
            url_list = self.out_queue.get()
            try:
                html = urllib2.urlopen(url_list).read()
                title_txt = re.findall("<title>(.*?)</title>", html)
                print title_txt
            except:
                pass

        self.out_queue.task_done()


queue = Queue.Queue()
out_queue = Queue.Queue()
urls = ['http://weather.yahoo.com', 'http://www.yahoo.com',  'http://wwww.jd.com']
for url in urls:
    queue.put(url)
for i in range(3):
    t = Foo(queue, out_queue)
    t.setDaemon(True)
    t.start()

for i in range(5):
    t = Consumer(out_queue)
    t.setDaemon(True)
    t.start()

queue.join()
out_queue.join()
