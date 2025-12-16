#ifndef MY_PROJECT_LOGGER_H
#define MY_PROJECT_LOGGER_H

#include <string>
#include <iostream>
#include <cstdio>

/**
 * 日志级别
 */
enum LogLevel
{
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
    NUM_LOG_LEVELS
};

/**
 * 日志输出函数类型
 */
typedef void (*OutputFunc)(const char *msg, int len);

/**
 * 日志刷新函数类型
 */
typedef void (*FlushFunc)();

/**
 * 设置日志输出函数
 */
void setOutput(OutputFunc);

/**
 * 设置日志刷新函数
 */
void setFlush(FlushFunc);

/**
 * 设置日志级别
 */
void setLogLevel(LogLevel level);

/**
 * 日志类
 */
class Logger
{
public:
    Logger(LogLevel level, const char *file, int line);
    ~Logger();

    /**
     * 获取日志流
     */
    std::ostream &stream();

    /**
     * 获取日志级别名称
     */
    static const char *logLevelName[NUM_LOG_LEVELS];

private:
    class Impl;
    Impl *impl_;
};

/**
 * 日志宏定义
 */
#define LOG_TRACE                    \
    if (Logger::logLevelName[TRACE]) \
    Logger(TRACE, __FILE__, __LINE__).stream()
#define LOG_DEBUG                    \
    if (Logger::logLevelName[DEBUG]) \
    Logger(DEBUG, __FILE__, __LINE__).stream()
#define LOG_INFO                    \
    if (Logger::logLevelName[INFO]) \
    Logger(INFO, __FILE__, __LINE__).stream()
#define LOG_WARN Logger(WARN, __FILE__, __LINE__).stream()
#define LOG_ERROR Logger(ERROR, __FILE__, __LINE__).stream()
#define LOG_FATAL Logger(FATAL, __FILE__, __LINE__).stream()

#endif // MY_PROJECT_LOGGER_H