#include <iostream>

template<typename T>
class ShareCount
{
    private:
        T *ptr; // 指向管理的对象
        int count; // 引用计数
    public:
    //禁止拷贝构造和赋值运算符
    ShareCount(const ShareCount&) = delete;
    ShareCount& operator=(const ShareCount&) = delete;

};
