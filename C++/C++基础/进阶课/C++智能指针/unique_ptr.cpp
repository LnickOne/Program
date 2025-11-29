/*
unique_ptr独享它所指向的对象，也就是说，同时只有一个unique_ptr指向同一个对象，当这个unique_ptr被销毁时，它所指向的对象也被销毁。
包含头文件：#include <memory>
template <class T, class D = default_delete<T>> //第一个参数表示指针指向的数据类型，第二个模板参数指定删除器，默认使用delete来释放内存
class unique_ptr
{
public:
    explicit unique_ptr(pointer p ) noexcept;//不可用于转换函数
    ~unique_ptr() noexcept;
    T& operator() const; //重载*运算符
    T*&operator->() const noexcept; //重载->操作符
    T *get();
    unique_ptr(unique_ptr<T> &&u);
    unique_ptr<T> &operator=(unique_ptr<T> &&u);
    T *release();
    void reset(T *p = nullptr);
private:
    pointer ptr;//内置的指针
}
*/