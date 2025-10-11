
from socket import *
HOST = ''
PORT = getservbyname("daytime", "UDP")
# sasas
UDP = socket(AF_INET, SOCK_DGRAM)
UDP.bind((HOST, PORT))
while True:
    data, addr = UDP.recvfrom(1024)
    if data == b'quit':
        break
    print "Recieve Data:", data.decode('utf-8')
    UDP.sendto(data, addr)

UDP.close()
