# coding:utf-8

from socket import *
from time import ctime

"""书本P475例子16.3.6 UDP时间戳服务器"""

HOST = ''
PORT = 21567
BUFSIZ = 1024
ADDR = (HOST, PORT)

udpSerSock = socket(AF_INET, SOCK_DGRAM)
udpSerSock.bind(ADDR)
print "waiting for message..."
while True:
    data, addr = udpSerSock.recvfrom(BUFSIZ)
    udpSerSock.sendto("[%s] %s" % (ctime(), data), addr)
    print "...receoved from and returned to:", addr
udpSerSock.close()
