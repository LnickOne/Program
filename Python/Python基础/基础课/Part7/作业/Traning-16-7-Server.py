# coding=utf-8

from socket import *

HOST = ''
PORT = 50007
server = socket(AF_INET, SOCK_STREAM)
server.bind((HOST, PORT))
server.listen(1)
conn, addr = server.accept()
print 'Connected by:', addr
while True:
    data = conn.recv(1024)
    if not data:
        break
    print addr, ": ", data
    data = raw_input('>')
    if data == 'quit':
        break
    conn.sendall(data)
conn.close()
