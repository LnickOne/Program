#pragma once

#include <utility> // 用于std::move

template <class T>
class MyArray
{
public:
    // 默认构造函数
    MyArray() : pAddress(nullptr), m_Capacity(0), m_Size(0) {}

    // 构造函数
    explicit MyArray(int capacity) : m_Capacity(capacity), m_Size(0)
    {
        if (capacity > 0)
        {
            pAddress = new T[capacity];
        }
        else
        {
            pAddress = nullptr;
        }
    }

    // 拷贝构造
    MyArray(const MyArray &arr) : m_Capacity(arr.m_Capacity), m_Size(arr.m_Size)
    {
        if (m_Capacity > 0)
        {
            pAddress = new T[m_Capacity];
            for (int i = 0; i < m_Size; i++)
            {
                pAddress[i] = arr.pAddress[i]; // 直接访问，避免递归
            }
        }
        else
        {
            pAddress = nullptr;
        }
    }

    // 移动构造
    MyArray(MyArray &&arr) noexcept : pAddress(arr.pAddress),
                                      m_Capacity(arr.m_Capacity),
                                      m_Size(arr.m_Size)
    {
        // 将原对象置于有效但不确定的状态
        arr.pAddress = nullptr;
        arr.m_Capacity = 0;
        arr.m_Size = 0;
    }

    // 重载= 操作符
    MyArray &operator=(const MyArray &myarray)
    {
        if (this != &myarray)
        { // 自我赋值检查
            // 释放原有资源
            delete[] pAddress;

            // 分配新资源并拷贝
            m_Capacity = myarray.m_Capacity;
            m_Size = myarray.m_Size;

            if (m_Capacity > 0)
            {
                pAddress = new T[m_Capacity];
                for (int i = 0; i < m_Size; i++)
                {
                    pAddress[i] = myarray.pAddress[i]; // 直接访问，避免递归
                }
            }
            else
            {
                pAddress = nullptr;
            }
        }
        return *this;
    }

    // 移动赋值操作符
    MyArray &operator=(MyArray &&myarray) noexcept
    {
        if (this != &myarray)
        { // 自我赋值检查
            // 释放原有资源
            delete[] pAddress;

            // 移动资源
            pAddress = myarray.pAddress;
            m_Capacity = myarray.m_Capacity;
            m_Size = myarray.m_Size;

            // 将原对象置于有效但不确定的状态
            myarray.pAddress = nullptr;
            myarray.m_Capacity = 0;
            myarray.m_Size = 0;
        }
        return *this;
    }

    // 重载[] 操作符
    T &operator[](int index)
    {
        // 可以添加边界检查
        // if (index < 0 || index >= m_Size) throw std::out_of_range("Index out of range");
        return pAddress[index];
    }

    // 对const对象的[]操作符重载
    const T &operator[](int index) const
    {
        return pAddress[index];
    }

    // 尾插法
    void Push_back(const T &val)
    {
        if (m_Capacity == m_Size)
        {
            return;
        }
        pAddress[m_Size] = val;
        m_Size++;
    }

    // 移动版本的尾插法
    void Push_back(T &&val)
    {
        if (m_Capacity == m_Size)
        {
            return;
        }
        pAddress[m_Size] = std::move(val);
        m_Size++;
    }

    // 尾删法
    void Pop_back()
    {
        if (m_Size > 0)
        {
            m_Size--;
        }
    }

    // 获取数组容量
    int getCapacity() const
    {
        return m_Capacity;
    }

    // 获取数组大小
    int getSize() const
    {
        return m_Size;
    }

    // 析构
    ~MyArray()
    {
        delete[] pAddress;
        // 以下初始化是可选的，因为对象即将销毁
        pAddress = nullptr;
        m_Capacity = 0;
        m_Size = 0;
    }

private:
    T *pAddress;    // 指向一个堆空间，这个空间存储真正的数据
    int m_Capacity; // 容量
    int m_Size;     // 大小
};