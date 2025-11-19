# coding=utf-8

"""书本P47例子16.4 UDP时间戳客户端"""

from socket import *

# 让服务器的名字不要在代码里写死，要允许用户指定一个主机名和端口，只有在两个值都没有输入的时候，才使用默认值。
host = raw_input('host: ')
port = raw_input('port: ')
if host == '':
    host = '127.0.0.1'
if port == '':
    port = '21567'
BUFSIZ = 1024
ADDR = (host, int(port))

udpCliSock = socket(AF_INET, SOCK_DGRAM)
while True:
    data = raw_input('>')
    if not data:
        break
    udpCliSock.sendto(data, ADDR)
    data, ADDR = udpCliSock.recvfrom(BUFSIZ)
    if not data:
        break
    print data
udpCliSock.close()
