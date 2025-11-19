#include <iostream>
#include <string>
#include <thread>
using namespace std;
// 工厂模式就是定义一个创建对象的接口，让其子类自己决定实例化哪一个工厂类，工厂模式使其创建过程延迟到子类进行。
class Product
{
public:
    virtual void show() = 0;
    virtual ~Product() = 0;
};
// 纯虚析构函数需要提供实现
inline Product::~Product(){}
class productA : public Product
{
public:
    void show() override
    {
        cout << "我是产品A" << endl;
    }
    ~productA() override
    {
        cout << "产品A被销毁" << endl;
    }
};

class productB : public Product
{
public:
    void show() override
    {
        cout << "我是产品B" << endl;
    }
    ~productB() override
    {
        cout << "产品B被销毁" << endl;
    }
};
class Factory
{
public:
    virtual Product *createProduct() = 0;
};

class FactoryA : public Factory
{
public:
    Product *createProduct() override
    {
        return new productA();
    }
};

class FactoryB : public Factory
{
public:
    Product *createProduct() override
    {
        return new productB();
    }
};

int main()
{
    FactoryA factoryA;
    FactoryB factoryB;
    Product *productA = factoryA.createProduct();
    Product *productB = factoryB.createProduct();

    if (productA != nullptr)
    {
        productA->show();
        delete productA;
        productA = nullptr;
    }
    if (productB != nullptr)
    {
        productB->show();
        delete productB;
        productB = nullptr;
    }

    return 0;
}