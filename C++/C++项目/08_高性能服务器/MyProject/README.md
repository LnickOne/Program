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

## 第二阶段项目结构

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
│   └── Logger.h         # 日志器（第二阶段）
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
│   └── main.cc          # 服务器主程序（更新）
└── build/               # 构建目录（自动生成）
    ├── CMakeCache.txt
    ├── CMakeFiles/
    ├── Makefile
    ├── cmake_install.cmake
    └── server           # 编译生成的可执行文件
```

## 核心组件详细说明

### 1. 事件循环 (EventLoop)

```cpp
class EventLoop : noncopyable
{
public:
    using Functor = std::function<void()>;

    EventLoop();
    ~EventLoop();

    void loop();
    void quit();

    void runInLoop(Functor cb);
    void queueInLoop(Functor cb);

    void updateChannel(Channel *channel);
    void removeChannel(Channel *channel);
    bool hasChannel(Channel *channel);

    // 其他方法...

private:
    void wakeup();
    void handleRead();
    void doPendingFunctors();

    // 成员变量...
};
```

- 实现了事件循环的核心逻辑
- 支持事件的注册、更新和移除
- 提供了跨线程的任务执行机制
- 使用wakeupFd实现事件循环的唤醒

### 2. 事件通道 (Channel)

```cpp
class Channel : noncopyable
{
public:
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void(Timestamp)>;

    Channel(EventLoop *loop, int fd);
    ~Channel();

    void handleEvent(Timestamp receiveTime);

    void setReadCallback(ReadEventCallback cb) { readCallback_ = std::move(cb); }
    void setWriteCallback(EventCallback cb) { writeCallback_ = std::move(cb); }
    void setCloseCallback(EventCallback cb) { closeCallback_ = std::move(cb); }
    void setErrorCallback(EventCallback cb) { errorCallback_ = std::move(cb); }

    // 事件操作方法...

private:
    void update();

    // 成员变量...
};
```

- 封装了文件描述符和事件类型
- 管理事件的回调函数
- 与EventLoop和Poller协同工作
- 实现了事件的处理和分发

### 3. IO多路复用 (Poller/EPollPoller)

```cpp
class Poller : noncopyable
{
public:
    using ChannelList = std::vector<Channel*>;

    Poller(EventLoop *loop);
    virtual ~Poller();

    virtual Timestamp poll(int timeoutMs, ChannelList *activeChannels) = 0;
    virtual void updateChannel(Channel *channel) = 0;
    virtual void removeChannel(Channel *channel) = 0;
    virtual bool hasChannel(Channel *channel) const = 0;

    // 其他方法...
};
```

- 定义了IO多路复用的通用接口
- 基于epoll实现了高效的事件等待和分发
- 支持事件的注册、更新和移除
- 提供了高效的事件处理机制

## 第二阶段技术特点

### 1. 高性能设计
- 使用epoll作为IO多路复用机制，支持百万级并发连接
- 采用非阻塞IO提高服务器的吞吐量
- 实现了高效的事件分发机制，避免不必要的上下文切换
- 使用时间戳工具精确管理超时事件

### 2. 可靠性设计
- 严格的错误处理和资源管理
- 使用RAII原则管理文件描述符和资源
- 提供了线程安全的设计，确保多线程环境下的正确性

### 3. 可扩展性设计
- 组件之间低耦合，便于扩展和维护
- 支持添加新的事件类型和处理方式
- 便于扩展到多线程模型

### 4. 易用性设计
- 提供了简洁的API接口
- 支持Lambda表达式作为回调函数
- 提供了详细的日志记录功能

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

## 第二阶段与第一阶段的区别

| 特性 | 第一阶段 | 第二阶段 |
|------|----------|----------|
| 架构模式 | 阻塞式IO | 事件驱动（Reactor模式） |
| IO多路复用 | 无 | epoll |
| 并发处理 | 单连接 | 高并发连接 |
| 事件管理 | 无 | 完整的事件注册、更新和处理机制 |
| 线程支持 | 单线程 | 线程安全设计，支持跨线程任务执行 |
| 扩展性 | 有限 | 高度可扩展，支持多线程模型 |
| 性能 | 基础 | 高性能，支持百万级并发连接 |

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

### 核心组件

#### TcpConnection
管理单个TCP连接，处理连接的建立、数据收发和关闭。

**关键功能**：
- 连接状态管理（连接中、已连接、断开中、已断开）
- 非阻塞IO操作（读/写）
- 输入/输出缓冲区管理
- 事件回调机制

**核心代码**：
```cpp
class TcpConnection : noncopyable {
public:
    // 连接状态枚举
    enum StateE { kDisconnected, kConnecting, kConnected, kDisconnecting };
    
    // 构造函数
    TcpConnection(EventLoop* loop, const std::string& name, int sockfd,
                 const InetAddress& localAddr, const InetAddress& peerAddr);
    
    // 发送数据
    void send(const std::string& message);
    
    // 关闭连接
    void shutdown();
    
    // 设置回调函数
    void setConnectionCallback(const ConnectionCallback& cb);
    void setMessageCallback(const MessageCallback& cb);
    void setWriteCompleteCallback(const WriteCompleteCallback& cb);
    void setCloseCallback(const CloseCallback& cb);
    
    // 获取连接状态
    bool connected() const { return state_ == kConnected; }
    
private:
    // 处理IO事件
    void handleRead(Timestamp receiveTime);
    void handleWrite();
    void handleClose();
    void handleError();
    
    // 其他成员变量...
};
```

#### TcpServer
负责监听端口，接受新连接，并管理所有TcpConnection对象。

**关键功能**：
- 监听指定地址和端口
- 接受新连接并创建TcpConnection对象
- 管理所有活跃连接
- 提供统一的事件回调接口

**核心代码**：
```cpp
class TcpServer : noncopyable {
public:
    // 构造函数
    TcpServer(EventLoop* loop, const InetAddress& listenAddr, const std::string& nameArg);
    
    // 启动服务器
    void start();
    
    // 设置回调函数
    void setConnectionCallback(const ConnectionCallback& cb);
    void setMessageCallback(const MessageCallback& cb);
    void setWriteCompleteCallback(const WriteCompleteCallback& cb);
    
private:
    // 处理新连接
    void newConnection(int sockfd, const InetAddress& peerAddr);
    
    // 移除连接
    void removeConnection(const std::shared_ptr<TcpConnection>& conn);
    
    // 其他成员变量...
};
```

#### Acceptor
负责监听新的连接请求，并在有新连接时调用回调函数。

**关键功能**：
- 监听套接字的创建和配置
- 处理新连接的接受
- 解决文件描述符耗尽问题

**核心代码**：
```cpp
class Acceptor : noncopyable {
public:
    // 构造函数
    Acceptor(EventLoop* loop, const InetAddress& listenAddr);
    
    // 设置新连接回调
    void setNewConnectionCallback(const NewConnectionCallback& cb);
    
    // 开始监听
    void listen();
    
    // 是否正在监听
    bool listenning() const { return listenning_; }
    
private:
    // 处理可读事件
    void handleRead();
    
    // 其他成员变量...
};
```

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

### 技术特点

1. **完整的连接生命周期管理**：从连接建立到关闭的全过程管理
2. **事件驱动的数据传输**：基于Reactor模式的非阻塞IO操作
3. **高效的缓冲区设计**：输入输出缓冲区确保数据完整性
4. **统一的回调接口**：简化业务逻辑的实现
5. **优雅的错误处理**：全面的错误检测和处理机制
6. **线程安全设计**：支持在多线程环境下使用

### 与前两阶段的区别

| 特性 | 第一阶段 | 第二阶段 | 第三阶段 |
|------|----------|----------|----------|
| 架构模式 | 阻塞式IO | 事件驱动 | 事件驱动+连接管理 |
| 连接管理 | 无 | 无 | 完整的TCP连接生命周期管理 |
| 服务器功能 | 基础Socket | 事件循环 | 完整的TCP服务器 |
| 组件数量 | 4 | 7 | 10 |
| 功能完整性 | 基础 | 核心架构 | 可用的TCP服务器 |

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
