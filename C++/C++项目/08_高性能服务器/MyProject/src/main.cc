#include <iostream>
#include "EventLoop.h"
#include "Logger.h"
#include <thread>

int main()
{
    // 初始化日志系统
    setLogLevel(DEBUG);

    // 创建一个事件循环对象
    EventLoop loop;

    LOG_INFO << "Main thread ID: " << std::this_thread::get_id();

    // 在事件循环中运行一个定时任务
    loop.runInLoop([]()
                   { LOG_INFO << "Running in loop thread: " << std::this_thread::get_id(); });

    // 运行事件循环
    loop.loop();

    return 0;
}