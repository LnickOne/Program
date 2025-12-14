// Copyright 2024. All Rights Reserved.
// Author: xxx@xxx.com

#ifndef MY_PROJECT_TIMESTAMP_H
#define MY_PROJECT_TIMESTAMP_H

#include <string>
#include <stdint.h>
#include <time.h>

/**
 * 时间戳类
 * 封装时间戳的表示和操作
 */
class Timestamp {
public:
    /**
     * 默认构造函数
     * 创建一个无效的时间戳
     */
    Timestamp() : microSecondsSinceEpoch_(0) {}

    /**
     * 构造函数
     * @param microSecondsSinceEpoch 从1970-01-01 00:00:00 UTC开始的微秒数
     */
    explicit Timestamp(int64_t microSecondsSinceEpoch) : microSecondsSinceEpoch_(microSecondsSinceEpoch) {}

    /**
     * 交换两个时间戳
     * @param that 要交换的时间戳
     */
    void swap(Timestamp& that) {
        std::swap(microSecondsSinceEpoch_, that.microSecondsSinceEpoch_);
    }

    /**
     * 转换为字符串表示
     * @return 时间戳的字符串表示
     */
    std::string toString() const;

    /**
     * 转换为格式化字符串
     * @return 格式化的时间字符串
     */
    std::string toFormattedString(bool showMicroseconds = true) const;

    /**
     * 检查时间戳是否有效
     * @return 是否有效
     */
    bool valid() const { return microSecondsSinceEpoch_ > 0; }

    /**
     * 获取微秒数
     * @return 微秒数
     */
    int64_t microSecondsSinceEpoch() const { return microSecondsSinceEpoch_; }

    /**
     * 获取秒数
     * @return 秒数
     */
    time_t secondsSinceEpoch() const {
        return static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);
    }

    /**
     * 获取当前时间
     * @return 当前时间的时间戳
     */
    static Timestamp now();

    /**
     * 创建一个无效的时间戳
     * @return 无效的时间戳
     */
    static Timestamp invalid() {
        return Timestamp();
    }

    /**
     * 从time_t创建时间戳
     * @param t 秒数
     * @return 时间戳
     */
    static Timestamp fromUnixTime(time_t t) {
        return fromUnixTime(t, 0);
    }

    /**
     * 从time_t和微秒创建时间戳
     * @param t 秒数
     * @param microseconds 微秒数
     * @return 时间戳
     */
    static Timestamp fromUnixTime(time_t t, int microseconds) {
        return Timestamp(static_cast<int64_t>(t) * kMicroSecondsPerSecond + microseconds);
    }

    /**
     * 每秒的微秒数
     */
    static const int kMicroSecondsPerSecond = 1000 * 1000;

private:
    int64_t microSecondsSinceEpoch_; // 从1970-01-01 00:00:00 UTC开始的微秒数
};

/**
 * 比较运算符
 */
inline bool operator<(Timestamp lhs, Timestamp rhs) {
    return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
}

inline bool operator==(Timestamp lhs, Timestamp rhs) {
    return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
}

/**
 * 计算两个时间戳的差值
 * @param high 较大的时间戳
 * @param low 较小的时间戳
 * @return 差值（秒）
 */
inline double timeDifference(Timestamp high, Timestamp low) {
    int64_t diff = high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();
    return static_cast<double>(diff) / Timestamp::kMicroSecondsPerSecond;
}

/**
 * 时间戳加上秒数
 * @param timestamp 原始时间戳
 * @param seconds 要添加的秒数
 * @return 新的时间戳
 */
inline Timestamp addTime(Timestamp timestamp, double seconds) {
    int64_t delta = static_cast<int64_t>(seconds * Timestamp::kMicroSecondsPerSecond);
    return Timestamp(timestamp.microSecondsSinceEpoch() + delta);
}

#endif // MY_PROJECT_TIMESTAMP_H