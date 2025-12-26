# MyProject 高性能服务器

## 项目简介

MyProject是一个基于C++11实现的高性能服务器框架，旨在构建一个模块化、可扩展、高性能的网络服务器，用于学习和理解网络编程的核心概念和技术。

## 项目架构概览

本项目采用基于Reactor模式的事件驱动架构，实现了一个完整的高性能Web服务器。项目分为七个阶段逐步实现，每个阶段构建在上一阶段的基础上，逐步增加功能和性能优化。

## 项目阶段实现

### 第一阶段：基础网络组件

**核心功能**：
- 不可拷贝基类 (noncopyable)：禁止拷贝构造和赋值运算符，确保资源管理安全
- 网络地址封装 (InetAddress)：封装sockaddr_in结构，提供IP地址和端口的转换功能
- 套接字封装 (Socket)：封装socket文件描述符和相关操作，支持TCP选项设置
- 简单服务器实现：创建监听地址和端口，接受客户端连接

**学习价值**：
- C++面向对象设计和封装技术
- RAII原则在资源管理中的应用
- 网络编程基础概念和系统调用
- 可移植性设计考虑

### 第二阶段：事件驱动架构

**核心功能**：
- 事件循环 (EventLoop)：实现事件驱动的核心机制
- 事件通道 (Channel)：封装文件描述符和事件类型
- IO多路复用 (Poller/EPollPoller)：基于epoll实现高效的事件等待和分发
- 时间戳工具 (Timestamp)：提供时间相关功能
- 线程安全工具 (Thread/MutexLock/Condition)：支持多线程编程
- 日志系统 (LogStream/Logger)：实现高效的日志记录

**学习价值**：
- Reactor模式的实现
- 高效的事件分发机制
- 非阻塞IO和IO多路复用技术
- 多线程编程和线程安全
- 日志系统设计

### 第三阶段：TCP连接管理

**核心功能**：
- TCP连接 (TcpConnection)：管理单个TCP连接的完整生命周期
- TCP服务器 (TcpServer)：负责监听端口、接受连接并管理所有连接
- 连接接受器 (Acceptor)：处理新连接的监听和接收

**学习价值**：
- TCP连接的生命周期管理
- 事件驱动的数据传输机制
- 服务器架构设计
- 网络编程高级技巧

### 第四阶段：HTTP协议解析

**核心功能**：
- HTTP上下文 (HttpContext)：管理HTTP请求的解析状态
- HTTP请求 (HttpRequest)：封装HTTP请求信息
- HTTP响应 (HttpResponse)：封装HTTP响应信息

**学习价值**：
- HTTP协议的完整实现细节
- 状态机模式在协议解析中的应用
- 高效的请求解析算法
- 响应生成机制

### 第五阶段：多线程处理

**核心功能**：
- 事件循环线程 (EventLoopThread)：每个线程运行一个事件循环
- 事件循环线程池 (EventLoopThreadPool)：管理多个事件循环线程

**学习价值**：
- 主从Reactor模式的实现
- 多线程环境下的负载均衡策略
- 充分利用多核CPU资源
- 线程池设计与实现

### 第六阶段：完整HTTP服务器

**核心功能**：
- HTTP服务器 (HttpServer)：整合前面所有组件，实现完整的HTTP服务
- 静态文件服务：支持静态文件的高效传输
- 响应缓存机制：基于内存的响应缓存系统，支持缓存过期时间
- 连接复用：支持HTTP Keep-Alive机制
- 错误处理与响应：完整的HTTP状态码支持

**学习价值**：
- Web服务器的完整实现
- 静态文件服务的设计与实现
- 缓存机制在Web服务器中的应用
- 连接复用技术原理
- 现代C++文件系统库的使用

### 第七阶段：性能测试与优化

**核心功能**：
- 性能测试工具：多线程HTTP客户端性能测试程序，支持配置并发客户端数量和请求数
- 线程安全修复：修复EventLoop中pendingFunctors_的线程安全问题
- 缓存策略优化：将简单FIFO缓存升级为LRU缓存
- 性能优化措施：优化事件循环、减少锁竞争、提升多线程并发能力

**学习价值**：
- 高性能服务器的测试方法和工具开发
- 多线程环境下的性能优化策略
- 线程安全问题的检测和修复
- 高效缓存策略的设计与实现
- 性能测试结果的分析与优化方向

## 项目结构

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
│   ├── main.cc          # 服务器主程序
│   └── PerformanceTest.cpp # 性能测试工具（第七阶段）
└── build/               # 构建目录（自动生成）
```

## 编译与运行

### 编译步骤

```bash
cd MyProject
mkdir -p build
cd build
cmake ..
make
```

### 运行服务器

编译成功后，在build目录下会生成server可执行文件：

```bash
./server
```

服务器默认在8080端口监听连接。

### 运行性能测试

编译性能测试工具：

```bash
g++ -std=c++11 -pthread src/PerformanceTest.cpp -o PerformanceTest
```

运行性能测试：

```bash
./PerformanceTest <端口> <客户端数量> <每个客户端请求数>
```

示例：
```bash
./PerformanceTest 8080 50 200
```

## 技术特点

### 1. 高性能设计
- 使用非阻塞IO和epoll提高服务器响应能力
- 启用FD_CLOEXEC标志，避免文件描述符泄露
- 支持TCP_NODELAY，减少网络延迟
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
- 基于Reactor模式的事件驱动架构
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

## 学习价值

通过学习和实现这个项目，你可以掌握：

- 现代C++编程技术和最佳实践
- 网络编程核心概念和系统调用
- 高性能服务器的设计与实现
- 事件驱动架构和Reactor模式
- 多线程编程和线程安全
- HTTP协议的完整实现
- 缓存策略和性能优化
- 软件架构设计和模块化开发

---

**版本**：第七阶段实现（v7.0）
**更新日期**：2025年12月10日
