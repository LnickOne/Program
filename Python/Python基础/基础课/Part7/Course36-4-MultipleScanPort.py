# coding:utf-8
import socket
import subprocess
import sys
import threading
import Queue
from datetime import datetime


class Scan(threading.Thread):

    def __init__(self, url_queue):
        self.url_queue = url_queue
        threading.Thread.__init__(self)

    def run(self):
        # while self.url_queue.full():
        while True:
            # gets the url from the queue
            url = self.url_queue.get()

            # download the file
            self.scan_ip(url)

            # send a singnal to the queue that the job is done
            self.url_queue.task_done()

    def scan_ip(self, url):
        remoteServerIP = socket.gethostbyname(url)
        print "-" * 60
        print "Please wait,scanning remote host", remoteServerIP
        print "-" * 60

        for port in range(1, 100):
            try:
                sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                result = sock.connect_ex((remoteServerIP, port))
                if result == 0:
                    print "Port {}:\t Open".format(port)
                sock.close()
            except Exception:
                sys.exit()
            sock.close()
queue = Queue.Queue()  # 用队列可以省掉锁
urls = ['www.csic.com.cn', "www.avic.com.cn", "www.faw.com.cn", "www.sinomach.com.cn"]

for url in urls:
    queue.put(url)

for i in range(3):  # 建立三个线程
    t = Scan(queue)
    t.setDaemon(True)  # 总之你其中一个线程反应慢就退出吧,
    t.start()

queue.join()
