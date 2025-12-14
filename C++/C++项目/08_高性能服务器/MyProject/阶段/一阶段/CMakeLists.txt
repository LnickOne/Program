cmake_minimum_required(VERSION 3.10)
project(MyNetServer)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

# 包含头文件目录
include_directories(include)

# 添加源文件
set(SRCS
    src/InetAddress.cc
    src/Socket.cc
    src/main.cc
)

# 创建可执行文件
add_executable(server ${SRCS})

# 链接库
target_link_libraries(server pthread)