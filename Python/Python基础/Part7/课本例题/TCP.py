# coding:utf-8

from SocketServer import (TCPServer as TCP, StreamRequestHandler as Request)
from time import ctime

HOST = '10.18.1.223'
PORT = 21561
ADDR = (HOST, PORT)


class MyRequestHandler(Request):

    def handle(self):
        print '客户来自:', self.client_address

        self.wfile.write('[%s] %s' % (ctime(), self.rfile.readline()))

tcpServer = TCP(ADDR, MyRequestHandler)
print "等待客户连接"
tcpServer.serve_forever()
