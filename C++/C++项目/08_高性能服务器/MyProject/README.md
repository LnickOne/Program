# MyProject 高性能服务器 - 第一阶段实现

## 项目简介

MyProject是一个基于C++11实现的高性能服务器框架，本项目旨在构建一个模块化、可扩展、高性能的网络服务器，用于学习和理解网络编程的核心概念和技术。

## 第一阶段完成的功能

第一阶段主要实现了高性能服务器的基础架构，包括以下核心组件：

### 1. 不可拷贝基类 (noncopyable)
- 实现了禁止拷贝构造和赋值运算符的基类
- 确保派生类对象不能被拷贝，避免资源管理问题

### 2. 网络地址封装 (InetAddress)
- 封装了`sockaddr_in`结构，提供了对IP地址和端口的封装
- 实现了IP地址和端口的转换功能（toIp、toPort、toIpPort）
- 支持地址的设置和获取操作

### 3. 套接字封装 (Socket)
- 封装了socket文件描述符和相关操作
- 提供了bind、listen、accept、shutdownWrite等核心方法
- 支持设置TCP选项（setTcpNoDelay、setReuseAddr、setReusePort、setKeepAlive）

### 4. 简单服务器实现 (main)
- 创建监听地址和端口
- 创建并配置监听套接字
- 绑定地址并开始监听
- 接受客户端连接并打印客户端信息

## 设计思路与实现理由

### 1. 面向对象设计
- 将底层的C API包装成C++类，提高代码的可维护性和可读性
- 每个类负责单一职责，符合单一职责原则

### 2. 资源管理 (RAII)
- 使用RAII原则管理socket文件描述符
- 确保资源在对象生命周期结束时正确释放，避免资源泄露

### 3. 可移植性
- 避免使用GNU扩展（如accept4、SOCK_NONBLOCK | SOCK_CLOEXEC）
- 使用标准的C++和系统调用，通过fcntl手动设置标志
- 提高代码在不同平台上的可移植性

### 4. 安全性
- 通过封装和显式的接口设计，减少使用底层API时可能出现的错误
- 使用explicit关键字防止意外的隐式类型转换

### 5. 代码复用
- 基础组件（如noncopyable）可以被其他类继承
- 封装的网络组件可以在后续阶段中复用

## 项目结构

```
MyProject/
├── CMakeLists.txt       # CMake构建配置文件
├── README.md            # 项目说明文档
├── include/             # 头文件目录
│   ├── noncopyable.h    # 不可拷贝基类
│   ├── InetAddress.h    # 网络地址封装
│   └── Socket.h         # 套接字封装
├── src/                 # 源代码目录
│   ├── InetAddress.cc   # 网络地址实现
│   ├── Socket.cc        # 套接字实现
│   └── main.cc          # 服务器主程序
└── build/               # 构建目录（自动生成）
    ├── CMakeCache.txt
    ├── CMakeFiles/
    ├── Makefile
    ├── cmake_install.cmake
    └── server           # 编译生成的可执行文件
```

## 编译与运行

### 编译步骤

1. 进入项目根目录
2. 创建并进入build目录
3. 运行cmake生成Makefile
4. 运行make编译项目

```bash
cd MyProject
mkdir -p build
cd build
cmake ..
make
```

### 运行服务器

编译成功后，在build目录下会生成server可执行文件，运行该文件即可启动服务器：

```bash
./server
```

服务器将在127.0.0.1:8888端口监听连接。当有客户端连接时，服务器会打印客户端的IP地址和端口信息，然后关闭连接并退出。

### 测试服务器

你可以使用telnet或nc命令来测试服务器：

```bash
telnet 127.0.0.1 8888
# 或
nc 127.0.0.1 8888
```

## 核心组件详细说明

### noncopyable 不可拷贝基类

```cpp
class noncopyable
{
public:
    noncopyable(const noncopyable &) = delete;
    noncopyable &operator=(const noncopyable &) = delete;
protected:
    noncopyable() = default;
    ~noncopyable() = default;
};
```

- 通过删除拷贝构造函数和赋值运算符，禁止派生类对象被拷贝
- 构造函数和析构函数设为protected，确保只能被派生类调用
- 适用于管理资源的类，避免资源泄露和重复释放

### InetAddress 网络地址封装

```cpp
class InetAddress
{
public:
    explicit InetAddress(uint16_t port = 0, std::string ip = "127.0.0.1");
    explicit InetAddress(const sockaddr_in &addr);

    std::string toIp() const;
    std::string toIpPort() const;
    uint16_t toPort() const;

    const sockaddr_in *getSockAddr() const;
    void setSockAddr(const sockaddr_in &addr);

private:
    sockaddr_in addr_;
};
```

- 封装了`sockaddr_in`结构，提供了对IP地址和端口的高级操作
- 支持从端口和IP地址创建对象，或从已有的`sockaddr_in`结构创建
- 提供了IP地址和端口的字符串转换功能，方便日志输出
- 使用`explicit`关键字防止意外的隐式类型转换

### Socket 套接字封装

```cpp
class Socket : noncopyable
{
public:
    explicit Socket(int sockfd);
    ~Socket();

    int fd() const;
    void bindAddress(const InetAddress &localaddr);
    void listen();
    int accept(InetAddress *peeraddr);

    void shutdownWrite();

    void setTcpNoDelay(bool on);
    void setReuseAddr(bool on);
    void setReusePort(bool on);
    void setKeepAlive(bool on);

private:
    const int sockfd_;
};
```

- 封装了socket文件描述符的创建、管理和关闭
- 提供了网络编程的核心操作：bind、listen、accept、shutdown
- 支持设置TCP选项，如禁用Nagle算法、地址重用、端口重用、保持连接等
- 使用RAII原则管理文件描述符，确保在对象销毁时正确关闭socket
- 避免使用GNU扩展，提高代码的可移植性

## 技术特点

### 1. 高性能设计
- 使用非阻塞I/O（O_NONBLOCK）提高服务器的响应能力
- 启用FD_CLOEXEC标志，避免文件描述符泄露到子进程
- 支持设置TCP_NODELAY，减少网络延迟

### 2. 可靠的资源管理
- 严格遵循RAII原则，确保资源正确释放
- 禁止拷贝构造和赋值，避免资源管理混乱

### 3. 良好的可移植性
- 避免使用平台特定的扩展
- 使用标准的C++11特性和系统调用
- 支持不同的Linux发行版

### 4. 清晰的代码结构
- 模块化设计，组件之间低耦合
- 每个类负责单一职责
- 完善的注释和文档

## 代码示例

### 服务器实现（main.cc）

```cpp
#include "noncopyable.h"
#include "InetAddress.h"
#include "Socket.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    // 创建InetAddress对象
    InetAddress addr(8888, "127.0.0.1");
    std::cout << "IP: " << addr.toIp() << std::endl;
    std::cout << "Port: " << addr.toPort() << std::endl;
    std::cout << "IP:Port: " << addr.toIpPort() << std::endl;

    // 创建Socket对象
    int listenfd = ::socket(AF_INET, SOCK_STREAM, 0);
    // 设置非阻塞
    int flags = ::fcntl(listenfd, F_GETFL, 0);
    ::fcntl(listenfd, F_SETFL, flags | O_NONBLOCK);
    // 设置CLOEXEC
    flags = ::fcntl(listenfd, F_GETFD, 0);
    ::fcntl(listenfd, F_SETFD, flags | FD_CLOEXEC);
    Socket socket(listenfd);

    // 绑定地址
    socket.bindAddress(addr);

    // 监听连接
    socket.listen();

    std::cout << "Server is listening on " << addr.toIpPort() << std::endl;

    // 等待连接
    InetAddress peeraddr;
    int connfd = socket.accept(&peeraddr);
    if (connfd >= 0)
    {
        std::cout << "New connection from " << peeraddr.toIpPort() << std::endl;
        ::close(connfd);
    }

    return 0;
}
```

## 第一阶段成果展示

编译生成的server可执行文件就是第一阶段的成果展示。它实现了一个简单但功能完整的TCP服务器，展示了以下核心功能：

1. **网络地址管理**：创建和使用InetAddress对象管理IP地址和端口
2. **套接字操作**：创建、绑定、监听和接受连接
3. **资源管理**：使用RAII原则管理文件描述符
4. **可移植性设计**：避免使用GNU扩展，使用标准系统调用
5. **错误处理**：基本的错误检查（虽然简单但框架已预留扩展空间）

这个简单的服务器为后续的开发奠定了坚实的基础，后续阶段将在此基础上添加事件循环、IO多路复用、多线程处理等高级功能。

## 后续规划

- **第二阶段**：实现事件循环（EventLoop）和IO多路复用（epoll）
- **第三阶段**：实现事件通道（Channel）和事件分发器
- **第四阶段**：实现TCP连接管理（TcpConnection）
- **第五阶段**：实现HTTP协议解析（HttpRequest/HttpResponse）
- **第六阶段**：实现多线程处理（EventLoopThread）
- **第七阶段**：实现完整的HTTP服务器功能

## 技术栈

- C++11：使用现代C++特性，如智能指针、lambda表达式、右值引用等
- CMake：跨平台的构建系统
- Linux系统编程：文件描述符、进程管理、信号处理等
- 网络编程：TCP/IP协议、socket API、IO多路复用等

## 学习价值

这个项目适合以下人群学习：

1. 想深入了解网络编程的C++开发者
2. 想学习高性能服务器设计的开发者
3. 想学习Linux系统编程和网络编程的学生
4. 想了解现代C++编程实践的开发者

通过学习这个项目，你可以掌握：

- 网络编程的核心概念和技术
- 高性能服务器的设计原理
- C++11的现代特性和最佳实践
- Linux系统编程和网络编程的实战经验
- 面向对象设计和RAII原则的应用


## 致谢

感谢所有为本项目做出贡献的开发者和用户！

---

**版本**：第一阶段实现（v1.0）
**更新日期**：2025年10月15日
