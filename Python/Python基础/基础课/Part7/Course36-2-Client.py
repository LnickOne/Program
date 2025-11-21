# coding:utf-8
import socket
HOST = '127.0.0.1'  # 远程主机
PORT = 2551  # 要和服务端的端口号一致
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

while True:
    str1 = raw_input("please input:")
    if str1 == "quit":
        break

    if not str1:
        break
    s.sendall(str1)
    data = s.recv(1024)
    print'Received', repr(data)
s.close()
