#pragma once

/*
 * noncopyable被继承后 派生类对象可以正常构造和析构
 * 但是派生类对象无法进行拷贝构造和赋值构造
 */

class noncopyable
{
public:
    noncopyable(const noncopyable &) = delete;
    noncopyable &operator=(const noncopyable &) = delete;
    // void operator=(const nocopyable &) =delete; //muduo将返回值变为void
protected:
    noncopyable() = default;
    ~noncopyable() = default;
};