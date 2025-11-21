# coding=utf-8
from socket import *

port = getservbyname("daytime", "UDP")
addr = ("127.0.0.1", port)
conn = socket(AF_INET, SOCK_DGRAM)
conn.sendto("something", addr)
data, addr = conn.recvfrom(1024)

if data:
    print "get message form Server:", data

conn.close()
