#pragma once // 防止头文件重复包含

/**
 * noncopyable被继承后 派生类对象可正常构造和析构
 * 但派生类对象无法进行拷贝构造和赋值构造
 **/
class noncopyable
{
public:
    noncopyable(const noncopyable &) = delete;            // 删除拷贝构造函数
    noncopyable &operator=(const noncopyable &) = delete; // 删除拷贝赋值运算符

    // void operator=(const noncopyable &) = delete;    // muduo将返回值变为void 这其实无可厚非
protected:
    noncopyable() = default;
    ~noncopyable() = default;
};