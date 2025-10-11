# coding:utf-8

import socket
import os
HOST = '127.0.0.1'  # 什么都不写即表示监控所有本地的链接
PORT = 2551
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # 第一个参数指互联网,第二个参数指TCP
s.bind((HOST, PORT))
s.listen(5)  # 监控五个客户端
while True:

    conn, addr = s.accept()  # 返回两个对象
    print 'Connected by', addr
    while True:
        data = conn.recv(1024)  # 接受1024字节信息
        if not data:
            break
        # data2 = os.popen(data)  # +r"C:\Users\manki\Desktop\Part7"
        # print data2.read()
        # conn.send(data2.read())
        conn.send(data)
        print data
conn.close()
