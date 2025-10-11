# coding:utf-8

from socket import *
from time import ctime


"""书本P472例子16.1 TCP时间戳服务器"""

HOST = 'localhost'
PORT = 21567
BUFSIZ = 1024
ADDR = (HOST, PORT)

tcpSerSock = socket(AF_INET, SOCK_STREAM)
tcpSerSock.bind(ADDR)
tcpSerSock.listen(5)

while True:
    print("waiting for connection...")
    tcpCliSock, addr = tcpSerSock.accept()
    print "...connected from:", addr

    while True:
        data = tcpCliSock.recv(BUFSIZ)
        if not data:
            break
        tcpCliSock.send("[%s] %s" % (ctime(), data))
    tcpCliSock.close()
tcpSerSock.close()
