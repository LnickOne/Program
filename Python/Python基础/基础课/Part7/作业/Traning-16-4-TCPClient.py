# coding:utf-8

"""书本P473例子16.2 TCP时间戳客户端"""

from socket import *

BUFSIZ = 1024
host = raw_input('host: ')
port = raw_input('port: ')  # 虽然端口号可以自己选,但是和服务器的端口号不匹配也不行

# 要允许用户指定一个主机名和端口，只有在两个值都没有输入的时候，才使用默认值。
if host == '':
    host = '127.0.0.1'
if port == '':
    port = '21567'
address = (host, int(port))

tcpClisSock = socket(AF_INET, SOCK_STREAM)
tcpClisSock.connect(address)
while True:
    data = raw_input('>')
    if not data:
        break
    tcpClisSock.send(data)
    data = tcpClisSock.recv(BUFSIZ)
    if not data:
        break
    print data
tcpClisSock.close()
