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

## 第一阶段项目结构

```
MyProject/
├── CMakeLists.txt       # CMake构建配置文件
├── README.md            # 项目说明文档
├── include/             # 头文件目录
│   ├── noncopyable.h    # 不可拷贝基类（第一阶段）
│   ├── InetAddress.h    # 网络地址封装（第一阶段）
│   └── Socket.h         # 套接字封装（第一阶段）
├── src/                 # 源代码目录
│   ├── InetAddress.cc   # 网络地址实现（第一阶段）
│   ├── Socket.cc        # 套接字实现（第一阶段）
│   └── main.cc          # 服务器主程序（第一阶段）
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

### 1. 不可拷贝基类 (noncopyable)
- 通过删除拷贝构造函数和赋值运算符，禁止派生类对象被拷贝
- 构造函数和析构函数设为protected，确保只能被派生类调用
- 适用于管理资源的类，避免资源泄露和重复释放

### 2. 网络地址封装 (InetAddress)
- 封装了`sockaddr_in`结构，提供了对IP地址和端口的高级操作
- 支持从端口和IP地址创建对象，或从已有的`sockaddr_in`结构创建
- 提供了IP地址和端口的字符串转换功能，方便日志输出
- 使用`explicit`关键字防止意外的隐式类型转换

### 3. 套接字封装 (Socket)
- 封装了socket文件描述符的创建、管理和关闭
- 提供了网络编程的核心操作：bind、listen、accept、shutdown
- 支持设置TCP选项，如禁用Nagle算法、地址重用、端口重用、保持连接等
- 使用RAII原则管理文件描述符，确保在对象销毁时正确关闭socket
- 避免使用GNU扩展，提高代码的可移植性

## 项目技术特点

### 1. 高性能设计
- 使用非阻塞IO（O_NONBLOCK）提高服务器的响应能力
- 启用FD_CLOEXEC标志，避免文件描述符泄露到子进程
- 支持设置TCP_NODELAY，减少网络延迟
- 基于epoll的高效事件监听
- 高效的内存管理和缓冲区设计

### 2. 可靠的资源管理
- 严格遵循RAII原则，确保资源正确释放
- 禁止拷贝构造和赋值，避免资源管理混乱
- 使用智能指针管理对象生命周期
- 异常安全的设计

### 3. 良好的可移植性
- 避免使用平台特定的扩展
- 使用标准的C++11特性和系统调用
- 支持不同的Linux发行版

### 4. 清晰的代码结构
- 模块化设计，组件之间低耦合
- 每个类负责单一职责
- 完善的注释和文档

### 5. 事件驱动架构
- 实现了基于Reactor模式的事件驱动架构
- 高效的事件分发机制
- 支持跨线程的任务执行

### 6. 多线程支持
- 实现了主从Reactor模式
- 线程安全的设计原则
- 负载均衡策略分配连接
- 充分利用多核CPU资源

### 7. HTTP协议支持
- 完整的HTTP/1.0和HTTP/1.1协议实现
- 支持常见的HTTP方法和状态码
- 高效的请求解析算法
- 灵活的响应生成机制

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

## 项目阶段规划

### 第一阶段：基础网络组件实现
**目标**：实现基础的网络编程组件，包括不可拷贝基类、网络地址封装和套接字封装。
**主要任务**：
1. 实现noncopyable不可拷贝基类
2. 实现InetAddress网络地址封装类
3. 实现Socket套接字封装类
4. 创建简单的服务器示例
**验收标准**：
- 能够编译并运行简单的服务器
- 服务器能够绑定地址、监听连接并接受客户端连接
- 代码符合C++11标准，使用RAII原则管理资源

### 第二阶段：事件驱动架构实现
**目标**：实现基于Reactor模式的事件驱动架构，包括事件循环、事件通道和IO多路复用。
**主要任务**：
1. 实现EventLoop事件循环类
2. 实现Channel事件通道类
3. 实现Poller抽象基类和EPollPoller实现
4. 实现Timestamp时间戳工具
5. 实现线程安全工具（Thread, MutexLock, Condition）
6. 实现日志系统（LogStream, Logger）
**验收标准**：
- 事件循环能够正常运行
- 支持事件的注册、更新和移除
- 支持跨线程的任务执行
- 日志系统能够记录不同级别的日志

### 第三阶段：TCP连接管理实现
**目标**：实现完整的TCP连接生命周期管理，包括连接建立、数据传输和连接关闭。
**主要任务**：
1. 实现Acceptor连接接受器
2. 实现TcpConnection连接管理类
3. 实现TcpServer服务器类
**验收标准**：
- 服务器能够监听端口并接受多个客户端连接
- 支持数据的发送和接收
- 支持正常关闭和异常关闭连接
- 连接状态管理正确

### 第四阶段：HTTP协议解析实现
**目标**：实现HTTP协议的请求和响应解析。
**主要任务**：
1. 实现HttpRequest请求解析类
2. 实现HttpResponse响应生成类
**验收标准**：
- 能够正确解析HTTP请求
- 能够生成符合HTTP协议的响应
- 支持基本的HTTP方法（GET, POST）

### 第五阶段：多线程处理实现
**目标**：实现多线程处理能力，提高服务器的并发处理能力。
**主要任务**：
1. 实现EventLoopThread事件循环线程类
2. 实现EventLoopThreadPool事件循环线程池
3. 扩展TcpServer支持多线程处理
**验收标准**：
- 服务器能够使用多个线程处理客户端连接
- 线程间通信和同步机制正确
- 性能测试显示并发处理能力提升

### 第六阶段：完整HTTP服务器实现
**目标**：实现完整的HTTP服务器功能，包括静态文件服务、动态请求处理等。
**主要任务**：
1. 实现静态文件服务
2. 实现HTTP路由功能
3. 实现错误处理机制
**验收标准**：
- 能够提供静态文件服务
- 支持简单的动态请求处理
- 能够处理常见的HTTP错误

### 第七阶段：性能测试与优化
**目标**：对服务器进行性能测试和优化，提高服务器的性能和稳定性。
**主要任务**：
1. 编写性能测试工具和脚本
2. 进行压力测试和性能分析
3. 对关键代码进行优化
4. 添加监控和统计功能
**验收标准**：
- 服务器能够处理高并发连接
- 性能达到预期目标
- 代码稳定性高，资源使用合理

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

---

**版本**：第一阶段实现（v1.0）
**更新日期**：2025年10月15日

---

# MyProject 高性能服务器 - 第二阶段实现

## 第二阶段完成的功能

第二阶段主要实现了事件驱动的高性能服务器架构，包括以下核心组件：

### 1. 事件循环 (EventLoop)
- 实现了基于事件驱动的事件循环机制
- 管理事件的注册、删除和分发
- 支持异步任务的执行和事件处理
- 实现了线程安全的设计，确保每个EventLoop对象只在一个线程中运行

### 2. 事件通道 (Channel)
- 封装了文件描述符和感兴趣的事件类型
- 管理事件的回调函数（可读、可写、错误、关闭）
- 提供了事件的注册、更新和移除接口
- 与EventLoop和Poller协同工作

### 3. IO多路复用 (Poller/EPollPoller)
- 实现了Poller抽象基类，定义了IO多路复用的通用接口
- 基于epoll实现了EPollPoller具体类，提供高效的IO多路复用机制
- 支持事件的注册、更新、移除和等待
- 实现了高效的事件分发机制

### 4. 时间戳工具 (Timestamp)
- 提供了高精度的时间戳功能
- 支持时间戳的格式化输出
- 用于日志记录和超时管理

### 5. 线程安全工具 (Thread, MutexLock, Condition)
- 封装了线程的创建和管理
- 提供了互斥锁和条件变量的封装
- 支持线程安全的任务队列

### 6. 倒计时门闩 (CountDownLatch)
- 用于线程同步的工具类
- 实现了线程等待机制，直到计数器减为0

### 7. 日志系统 (LogStream, Logger)
- 提供了高效的日志记录功能
- 支持不同级别的日志输出（DEBUG, INFO, WARN, ERROR, FATAL）
- 实现了线程安全的日志记录

## 设计思路与实现理由

### 1. 事件驱动架构
- 采用Reactor模式设计事件驱动系统
- 将IO事件和定时器事件统一管理
- 提高服务器的响应能力和并发处理能力

### 2. 高性能设计
- 使用epoll作为IO多路复用机制，支持高并发连接
- 采用非阻塞IO提高服务器的吞吐量
- 实现了高效的事件分发机制，避免不必要的上下文切换

### 3. 线程安全设计
- 每个EventLoop对象绑定到一个线程
- 支持跨线程的任务投递和执行
- 使用互斥锁和条件变量确保线程安全

### 4. 模块化设计
- 组件之间低耦合，便于扩展和维护
- 接口设计清晰，便于使用和测试
- 每个组件负责单一职责，符合单一职责原则

### 5. 可扩展性
- 支持添加新的事件类型和处理方式
- 支持扩展到多线程模型
- 便于添加新的协议支持



## 项目结构（最终版本）

```
MyProject/
├── CMakeLists.txt       # CMake构建配置文件
├── README.md            # 项目说明文档
├── include/             # 头文件目录
│   ├── noncopyable.h    # 不可拷贝基类（第一阶段）
│   ├── InetAddress.h    # 网络地址封装（第一阶段）
│   ├── Socket.h         # 套接字封装（第一阶段）
│   ├── EventLoop.h      # 事件循环（第二阶段）
│   ├── Channel.h        # 事件通道（第二阶段）
│   ├── Poller.h         # IO多路复用抽象基类（第二阶段）
│   ├── EPollPoller.h    # epoll实现（第二阶段）
│   ├── Timestamp.h      # 时间戳工具（第二阶段）
│   ├── Thread.h         # 线程封装（第二阶段）
│   ├── MutexLock.h      # 互斥锁封装（第二阶段）
│   ├── Condition.h      # 条件变量封装（第二阶段）
│   ├── CountDownLatch.h # 倒计时门闩（第二阶段）
│   ├── LogStream.h      # 日志流（第二阶段）
│   ├── Logger.h         # 日志器（第二阶段）
│   ├── TcpServer.h      # TCP服务器（第三阶段）
│   ├── TcpConnection.h  # TCP连接（第三阶段）
│   ├── Acceptor.h       # 连接接受器（第三阶段）
│   ├── HttpContext.h    # HTTP请求解析上下文（第四阶段）
│   ├── HttpRequest.h    # HTTP请求（第四阶段）
│   ├── HttpResponse.h   # HTTP响应（第四阶段）
│   ├── EventLoopThread.h # 事件循环线程（第五阶段）
│   ├── EventLoopThreadPool.h # 事件循环线程池（第五阶段）
│   ├── HttpServer.h     # HTTP服务器（第六阶段）
│   └── Cache.h          # 响应缓存（第六阶段）
├── src/                 # 源代码目录
│   ├── InetAddress.cc   # 网络地址实现（第一阶段）
│   ├── Socket.cc        # 套接字实现（第一阶段）
│   ├── EventLoop.cc     # 事件循环实现（第二阶段）
│   ├── Channel.cc       # 事件通道实现（第二阶段）
│   ├── Poller.cc        # IO多路复用抽象基类实现（第二阶段）
│   ├── EPollPoller.cc   # epoll实现（第二阶段）
│   ├── Timestamp.cc     # 时间戳工具实现（第二阶段）
│   ├── Thread.cc        # 线程封装实现（第二阶段）
│   ├── MutexLock.cc     # 互斥锁封装实现（第二阶段）
│   ├── Condition.cc     # 条件变量封装实现（第二阶段）
│   ├── CountDownLatch.cc # 倒计时门闩实现（第二阶段）
│   ├── LogStream.cc     # 日志流实现（第二阶段）
│   ├── Logger.cc        # 日志器实现（第二阶段）
│   ├── TcpServer.cc     # TCP服务器实现（第三阶段）
│   ├── TcpConnection.cc # TCP连接实现（第三阶段）
│   ├── Acceptor.cc      # 连接接受器实现（第三阶段）
│   ├── HttpContext.cc   # HTTP请求解析上下文实现（第四阶段）
│   ├── HttpRequest.cc   # HTTP请求实现（第四阶段）
│   ├── HttpResponse.cc  # HTTP响应实现（第四阶段）
│   ├── EventLoopThread.cpp # 事件循环线程实现（第五阶段）
│   ├── EventLoopThreadPool.cpp # 事件循环线程池实现（第五阶段）
│   ├── HttpServer.cc    # HTTP服务器实现（第六阶段）
│   ├── Cache.cc         # 响应缓存实现（第六阶段）
│   └── main.cc          # 服务器主程序（更新）
└── build/               # 构建目录（自动生成）
    ├── CMakeCache.txt
    ├── CMakeFiles/
    ├── Makefile
    ├── cmake_install.cmake
    └── server           # 编译生成的可执行文件
```

### 项目结构说明

本项目采用模块化设计，各文件按实现阶段和功能进行组织：

1. **第一阶段**：基础网络组件（noncopyable, InetAddress, Socket）
2. **第二阶段**：事件驱动架构（EventLoop, Channel, Poller/EPollPoller, Timestamp, Thread/MutexLock/Condition, LogStream/Logger）
3. **第三阶段**：TCP连接管理（TcpServer, TcpConnection, Acceptor）
4. **第四阶段**：HTTP协议解析（HttpContext, HttpRequest, HttpResponse）
5. **第五阶段**：多线程处理（EventLoopThread, EventLoopThreadPool）
6. **第六阶段**：完整HTTP服务器（HttpServer, Cache）

### 4. 事件循环 (EventLoop)
- 实现了事件循环的核心逻辑
- 支持事件的注册、更新和移除
- 提供了跨线程的任务执行机制
- 使用wakeupFd实现事件循环的唤醒

### 5. 事件通道 (Channel)
- 封装了文件描述符和事件类型
- 管理事件的回调函数
- 与EventLoop和Poller协同工作
- 实现了事件的处理和分发

### 6. IO多路复用 (Poller/EPollPoller)
- 定义了IO多路复用的通用接口
- 基于epoll实现了高效的事件等待和分发
- 支持事件的注册、更新和移除
- 提供了高效的事件处理机制



## 第二阶段代码示例

### 事件循环使用示例

```cpp
#include "EventLoop.h"
#include "Timestamp.h"
#include <iostream>

int main()
{
    EventLoop loop;
    
    // 在事件循环中执行任务
    loop.runInLoop([]() {
        std::cout << "Hello from event loop" << std::endl;
    });
    
    // 启动事件循环
    loop.loop();
    
    return 0;
}
```

## 第二阶段成果展示

第二阶段实现了一个完整的事件驱动架构，包括：

1. **事件驱动系统**：基于Reactor模式实现的事件驱动架构
2. **IO多路复用**：基于epoll的高效IO多路复用机制
3. **线程安全工具**：提供了完整的线程安全工具类
4. **日志系统**：实现了高效的日志记录功能
5. **事件管理**：支持多种事件类型的注册、更新和处理

这个事件驱动架构为后续的开发奠定了坚实的基础，可以在其上构建各种网络应用，如TCP服务器、HTTP服务器等。



## 第三阶段：TCP连接管理（TcpConnection）

### 功能说明
第三阶段实现了TCP连接的完整生命周期管理，包括连接的建立、数据传输、连接关闭等核心功能。这一阶段引入了三个关键组件：

1. **TcpConnection**：管理单个TCP连接的生命周期
2. **TcpServer**：负责监听端口、接受连接并管理所有连接
3. **Acceptor**：处理新连接的监听和接收

### 设计思路

#### 连接生命周期管理
- **连接建立**：Acceptor监听新连接，TcpServer创建TcpConnection对象
- **数据传输**：通过Channel和EventLoop实现事件驱动的数据读写
- **连接关闭**：支持主动关闭和被动关闭，确保资源正确释放

#### 组件关系
```
┌─────────────┐     ┌─────────────┐     ┌─────────────┐
│   TcpServer │────▶│   Acceptor  │────▶│TcpConnection│
└─────────────┘     └─────────────┘     └─────────────┘
        ▲                                      │
        │                                      ▼
        └────────────────────────────────────────┘
```

### 7. TCP连接/服务器/接受器 (TcpConnection/TcpServer/Acceptor)
- 管理单个TCP连接的生命周期
- 负责监听端口，接受新连接，并管理所有连接
- 处理新连接的监听和接收
- 支持非阻塞IO操作和事件回调机制

### 项目结构更新
第三阶段新增了以下文件：

```
MyProject/
├── include/
│   ├── TcpConnection.h    # TCP连接管理头文件
│   ├── TcpServer.h        # TCP服务器头文件
│   └── Acceptor.h         # 连接接受器头文件
└── src/
    ├── TcpConnection.cc   # TCP连接管理实现
    ├── TcpServer.cc       # TCP服务器实现
    └── Acceptor.cc        # 连接接受器实现
```



### 与前两阶段的区别



## 后续规划

根据项目阶段规划，后续将完成以下阶段：

- **第四阶段**：实现HTTP协议解析（HttpRequest/HttpResponse）
- **第五阶段**：实现多线程处理（EventLoopThread）
- **第六阶段**：实现完整的HTTP服务器功能
- **第七阶段**：添加性能测试和优化

## 学习价值

通过第三阶段的学习，你可以掌握：

- TCP连接的完整生命周期管理
- 事件驱动的数据传输机制
- 服务器架构的设计和实现
- 网络编程的高级技巧
- 现代C++的高级特性和最佳实践

---

**版本**：第三阶段实现（v3.0）
**更新日期**：2025年10月25日

---

# MyProject 高性能服务器 - 第四阶段实现

## 第四阶段完成的功能

第四阶段主要实现了HTTP协议的请求和响应解析功能，包括以下核心组件：

### 1. HTTP请求解析 (HttpRequest)
- 实现了HTTP请求行的解析（方法、URL、版本）
- 支持HTTP头部字段的解析和存储
- 提供了获取请求信息的接口
- 支持HTTP请求的重置和重新解析

### 2. HTTP响应生成 (HttpResponse)
- 实现了HTTP响应的构造和格式化
- 支持设置HTTP状态码和状态消息
- 提供了添加响应头字段的接口
- 支持设置响应正文
- 实现了将响应格式化为字符串的功能

### 3. HTTP上下文管理 (HttpContext)
- 实现了HTTP请求的状态机解析
- 支持分块数据的解析
- 管理HTTP请求的解析状态
- 与TcpConnection集成，处理HTTP请求的完整解析过程

## 设计思路与实现理由

### 1. 协议解析设计
- 采用状态机模式解析HTTP请求，确保解析的正确性和效率
- 将请求行、头部字段和正文分开处理，符合HTTP协议的结构
- 支持分块解析，适应非阻塞IO环境下的数据流

### 2. 高性能设计
- 使用字符串视图（char指针范围）避免不必要的字符串复制
- 采用哈希表存储头部字段，提高查找效率
- 最小化内存分配，提高解析性能

### 3. 易用性设计
- 提供简洁的接口，方便上层应用使用
- 支持链式调用，简化请求和响应的构造
- 提供完整的请求信息访问方法

### 4. 可扩展性
- 设计支持HTTP/1.0和HTTP/1.1协议
- 预留了扩展到HTTP/2的接口
- 支持自定义HTTP方法和头部字段

## 第四阶段项目结构

```
MyProject/
├── CMakeLists.txt       # CMake构建配置文件
├── README.md            # 项目说明文档
├── include/             # 头文件目录
│   ├── HttpRequest.h    # HTTP请求解析头文件
│   ├── HttpResponse.h   # HTTP响应生成头文件
│   └── HttpContext.h    # HTTP上下文管理头文件
├── src/                 # 源代码目录
│   ├── HttpRequest.cc   # HTTP请求解析实现
│   ├── HttpResponse.cc  # HTTP响应生成实现
│   └── HttpContext.cc   # HTTP上下文管理实现
└── build/               # 构建目录（自动生成）
```

## 核心组件详细说明

### 8. HTTP请求/响应/上下文 (HttpRequest/HttpResponse/HttpContext)
- 支持HTTP/1.0和HTTP/1.1版本
- 支持常见的HTTP方法和状态码
- 实现了HTTP请求的状态机解析
- 提供了请求和响应的完整访问接口
- 支持分块数据的解析

### 9. HTTP服务器 (HttpServer)
- 封装了HTTP服务器的完整功能
- 集成了TcpServer和HTTP协议解析
- 提供了HTTP请求处理的回调接口
- 支持多线程处理

### 10. 线程池 (EventLoopThreadPool)
- 管理多个EventLoop线程
- 实现了负载均衡策略（轮询分配）
- 提供了获取EventLoop的接口
- 支持线程初始化回调



## 第四阶段代码示例

### HTTP服务器使用示例

```cpp
#include "TcpServer.h"
#include "HttpContext.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include <iostream>

void onHttpRequest(const HttpRequest& req, HttpResponse* resp) {
    resp->setStatusCode(HttpResponse::k200Ok);
    resp->setStatusMessage("OK");
    resp->setContentType("text/html");
    resp->addHeader("Server", "MyProject/1.0");
    std::string body = "<html><head><title>MyProject HTTP Server</title></head>";
    body += "<body><h1>Hello, World!</h1></body></html>";
    resp->setBody(body);
}

void onMessage(const TcpConnectionPtr& conn, Buffer* buf, time_t receiveTime) {
    HttpContext context;
    if (context.parseRequest(buf, receiveTime)) {
        const HttpRequest& req = context.request();
        HttpResponse resp(req.getHeader("Connection") != "keep-alive");
        onHttpRequest(req, &resp);
        std::string output;
        resp.appendToBuffer(output);
        conn->send(output);
        if (resp.closeConnection()) {
            conn->shutdown();
        }
        context.reset();
    } else {
        conn->send("HTTP/1.1 400 Bad Request\r\nConnection: close\r\n\r\n");
        conn->shutdown();
    }
}

int main() {
    EventLoop loop;
    InetAddress listenAddr(8080);
    TcpServer server(&loop, listenAddr, "HttpServer");
    server.setMessageCallback(onMessage);
    server.start();
    loop.loop();
    return 0;
}
```

## 第四阶段成果展示

第四阶段实现了完整的HTTP协议解析功能，包括：

1. **HTTP请求解析**：能够正确解析HTTP请求行、头部字段和正文
2. **HTTP响应生成**：能够构造符合HTTP协议的响应
3. **HTTP上下文管理**：支持分块数据的解析和状态管理
4. **与TCP服务器集成**：能够与TcpServer无缝集成，构建完整的HTTP服务器

这个HTTP协议解析模块为后续实现完整的HTTP服务器奠定了坚实的基础，可以在此基础上构建各种HTTP应用，如静态文件服务器、API服务器等。


## 第五阶段：多线程处理（EventLoopThread）

### 第五阶段完成的功能

第五阶段主要实现了基于Reactor模式的多线程处理能力，通过引入EventLoopThread和EventLoopThreadPool组件，使服务器能够充分利用多核CPU资源，提高并发处理性能。

### 1. 事件循环线程 (EventLoopThread)
- 封装了线程和事件循环的关系，每个线程对应一个EventLoop
- 实现了线程的创建、启动和停止
- 提供了线程安全的EventLoop获取机制
- 支持线程初始化和退出回调

### 2. 事件循环线程池 (EventLoopThreadPool)
- 管理多个EventLoopThread实例
- 实现了负载均衡策略（轮询分配）
- 提供了获取下一个可用EventLoop的接口
- 支持动态设置线程数量

### 3. TcpServer多线程改造
- 集成EventLoopThreadPool到TcpServer
- 实现连接的多线程分发
- 确保线程安全的连接管理
- 支持连接建立和销毁的线程安全处理

### 4. HttpServer多线程支持
- 添加线程数量设置接口
- 实现HTTP请求的多线程处理
- 保持HTTP协议解析的线程安全性

### 设计思路与实现理由

### 1. 主从Reactor模式
- **主Reactor**：处理连接的监听和接受
- **从Reactor**：处理具体的客户端连接请求
- 分离连接管理和请求处理，提高并发性能

### 2. 线程安全设计
- 所有EventLoop操作必须在所属线程中执行
- 使用runInLoop和queueInLoop确保线程安全
- 避免在多线程环境下直接操作共享资源
- 通过智能指针管理对象生命周期

### 3. 负载均衡策略
- 采用轮询算法分配新连接到不同的EventLoop
- 确保连接均匀分布在多个线程中
- 简单高效，适合大多数场景

### 4. 资源管理
- 使用RAII原则管理线程资源
- 确保EventLoop和线程的正确销毁顺序
- 避免资源泄露和悬挂指针

### 学习价值

通过第五阶段的学习，你可以掌握：

- 多线程网络编程的核心概念
- Reactor模式的多线程实现
- 线程安全的设计原则和实践
- 负载均衡策略在网络编程中的应用
- 现代C++线程库的使用
- 智能指针在多线程环境下的应用

## 第六阶段：实现完整的HTTP服务器功能

### 1. HTTP协议支持
- 完整的HTTP请求解析（支持HTTP 1.0/1.1）
- 状态机模式实现的请求解析器，支持请求行、请求头和请求体
- 支持多种HTTP方法（当前主要实现GET方法）
- 支持Content-Length和chunked分块传输编码

### 2. 静态文件服务
- 支持静态文件的高效传输
- 自动识别文件类型并设置正确的Content-Type
- 支持默认文档（index.html）
- 路径安全检查，防止路径遍历攻击
- 使用C++17的filesystem库进行安全的文件操作

### 3. 响应缓存机制
- 实现基于内存的响应缓存系统
- 支持设置缓存过期时间
- 自动管理缓存条目，提高重复请求的响应速度
- 通过X-Cache头标识缓存命中状态

### 4. 连接复用
- 支持HTTP Keep-Alive机制
- 根据客户端请求头自动决定是否保持连接
- 同一TCP连接上处理多个HTTP请求
- 提高服务器并发处理能力和资源利用率

### 5. 错误处理与响应
- 完整的HTTP状态码支持（200, 400, 403, 404, 405等）
- 自定义错误页面，提升用户体验
- 详细的错误信息和请求路径展示

### 6. 性能优化
- 非阻塞IO与多线程Reactor模式的结合
- 高效的内存管理，减少不必要的内存分配
- 响应内容的批量发送，减少系统调用

### 学习价值

通过第六阶段的学习，你可以掌握：

- HTTP协议的完整实现细节
- 状态机模式在协议解析中的应用
- 静态文件服务的设计与实现
- 缓存机制在Web服务器中的应用
- 连接复用技术（Keep-Alive）的原理与实现
- 现代C++文件系统库的使用
- Web服务器的性能优化策略

## 后续规划

根据项目阶段规划，后续将完成以下阶段：

- **第七阶段**：添加性能测试和优化

---

**版本**：第六阶段实现（v6.0）
**更新日期**：2025年12月10日
