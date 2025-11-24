#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h> //ip地址的操作api
#include <arpa/inet.h>  //ip地址的操作api
#include <unistd.h>     //操作系统的api
#include <cstring>
int main(int, char **)
{
    // 1.创建一个套接字
    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);

    // 2.绑定IP地址信息和端口号
}
