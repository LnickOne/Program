cmake_minimum_required(VERSION 3.10)
project(HttpComponentsTest)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

# 包含头文件目录（包括项目根目录的include）
include_directories(../include)

# 添加核心源文件（除了main.cc）
set(CORE_SRCS
    ../src/InetAddress.cc
    ../src/Socket.cc
    ../src/Channel.cc
    ../src/EPollPoller.cc
    ../src/EventLoop.cc
    ../src/Logger.cc
    ../src/Timestamp.cc
    ../src/Poller.cc
    ../src/TcpConnection.cc
    ../src/TcpServer.cc
    ../src/Acceptor.cc
    ../src/HttpRequest.cc
    ../src/HttpResponse.cc
    ../src/HttpContext.cc
    ../src/HttpServer.cc
)

# 添加测试源文件
set(TEST_SRCS
    test_http.cpp
)

# 创建测试可执行文件
add_executable(test_http ${CORE_SRCS} ${TEST_SRCS})

# 链接库
target_link_libraries(test_http pthread)