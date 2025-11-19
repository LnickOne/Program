# coding:utf-8

import socket

# 以下为服务端
HOST = '127.0.0.1'  # 什么都不写即表示监控所有本地的链接
PORT = 25510
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # 第一个参数指互联网,第二个参数指TCP
s.bind((HOST, PORT))
s.listen(5)  # 监控五个客户端
conn, addr = s.accept()  # 返回两个对象
print 'Connected by', addr
print conn
while 1:
    data = conn.recv(1024)  # 接受1024字节信息
    # print data
    if not data:
        break
    conn.sendall("from server" + data)
conn.close()
