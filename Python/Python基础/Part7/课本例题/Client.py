# coding:utf-8

from socket import *

HOST = '10.18.1.223'
PORT = 21561
ADDR = (HOST, PORT)

while True:
    tcpClient = socket(AF_INET, SOCK_STREAM)
    tcpClient.connect(ADDR)
    data = raw_input("input>")
    if not data:
        break
    tcpClient.send('%s' % data)
    data = tcpClient.recv(1024)
    if not data:
        break
    print data.strip()
    tcpClient.close()
