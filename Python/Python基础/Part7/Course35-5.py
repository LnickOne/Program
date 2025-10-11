# coding:utf-8
import Queue
import threading
import urllib2
import re


class Foo(threading.Thread):

    def __init__(self, queue):
        threading.Thread.__init__(self)
        self.queue = queue

    def run(self):
        while True:
            url = self.queue.get()
            self.download_url(url)
            self.queue.task_done()

    def download_url(self, url):
        html = urllib2.urlopen(url).read()
        text_title = re.findall(r'<title>(.*?)</title>', html)
        print text_title

queue = Queue.Queue()
urls = ['http://weather.yahoo.com', 'http://www.yahoo.com',  'http://wwww.sogo.com']
for url in urls:
    queue.put(url)


for i in range(3):
    t = Foo(queue)
    t.setDaemon(True)
    t.start()
t.join()
#     print q.get()
