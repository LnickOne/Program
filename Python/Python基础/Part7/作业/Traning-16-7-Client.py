# coding=utf-8

from socket import *

HOST = '127.0.0.1'
PORT = 50007
conn = socket(AF_INET, SOCK_STREAM)
conn.connect((HOST, PORT))
while True:
    data = raw_input('>')
    if data == 'quit':
        break
    conn.sendall(data)
    data = conn.recv(1024)
    if not data:
        break
    print conn.getpeername(),  ': ', data
conn.close()
