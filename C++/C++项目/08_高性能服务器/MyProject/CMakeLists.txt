cmake_minimum_required(VERSION 3.10)
project(MyNetServer)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

# 包含头文件目录
include_directories(include)

# 添加源文件
set(SRCS
    src/InetAddress.cc
    src/Socket.cc
    src/Channel.cc
    src/EPollPoller.cc
    src/EventLoop.cc
    src/EventLoopThread.cpp
    src/EventLoopThreadPool.cpp
    src/Logger.cc
    src/Timestamp.cc
    src/Poller.cc
    src/TcpConnection.cc
    src/TcpServer.cc
    src/Acceptor.cc
    src/HttpRequest.cc
    src/HttpResponse.cc
    src/HttpContext.cc
    src/HttpServer.cc
    src/Cache.cc
    src/main.cc
)

# 创建可执行文件
add_executable(server ${SRCS})

# 链接库
target_link_libraries(server pthread)

# 链接filesystem库（对于某些编译器版本可能需要）
if(CMAKE_COMPILER_IS_GNUCXX AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
    target_link_libraries(server stdc++fs)
endif()