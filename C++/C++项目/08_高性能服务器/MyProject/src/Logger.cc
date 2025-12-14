// Copyright 2024. All Rights Reserved.
// Author: xxx@xxx.com

#include "Logger.h"
#include "Timestamp.h"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <mutex>

/**
 * 日志级别名称
 */
const char *Logger::logLevelName[NUM_LOG_LEVELS] = {
    "TRACE",
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL",
};

/**
 * 日志实现类
 */
class Logger::Impl
{
public:
    Impl(LogLevel level, const char *file, int line)
        : stream_(),
          level_(level),
          line_(line),
          basename_(file),
          timestamp_(Timestamp::now())
    {
        formatTime();
    }

    void formatTime()
    {
        std::string formatted = timestamp_.toFormattedString(false);
        stream_ << formatted << " ";
    }

    std::ostringstream stream_;
    LogLevel level_;
    int line_;
    const char *basename_;
    Timestamp timestamp_;
};

/**
 * 日志输出函数
 */
static OutputFunc g_output = [](const char *msg, int len)
{
    std::cout.write(msg, len);
};

/**
 * 日志刷新函数
 */
static FlushFunc g_flush = []()
{
    std::cout.flush();
};

/**
 * 日志级别
 */
static LogLevel g_logLevel = INFO;

/**
 * 日志构造函数
 */
Logger::Logger(LogLevel level, const char *file, int line)
    : impl_(new Impl(level, file, line))
{
    impl_->stream_ << Logger::logLevelName[level] << " ";
}

/**
 * 日志析构函数
 */
Logger::~Logger()
{
    impl_->stream_ << " - " << impl_->basename_ << ":" << impl_->line_ << "\n";
    const std::string &buf = impl_->stream_.str();
    g_output(buf.c_str(), buf.size());
    if (impl_->level_ == FATAL)
    {
        g_flush();
        abort();
    }
    delete impl_;
}

/**
 * 获取日志流
 */
std::ostream &Logger::stream()
{
    return impl_->stream_;
}

/**
 * 设置日志输出函数
 */
void setOutput(OutputFunc out)
{
    g_output = out;
}

/**
 * 设置日志刷新函数
 */
void setFlush(FlushFunc flush)
{
    g_flush = flush;
}

/**
 * 设置日志级别
 */
void setLogLevel(LogLevel level)
{
    g_logLevel = level;
}