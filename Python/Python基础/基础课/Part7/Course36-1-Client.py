# coding:utf-8
import socket
HOST = '127.0.0.1'  # 远程主机
PORT = 25510  # 要和服务端的端口号一致
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
s.sendall(("from client Hello,world"))
data = s.recv(1024)
s.close()
print 'Received', repr(data)
