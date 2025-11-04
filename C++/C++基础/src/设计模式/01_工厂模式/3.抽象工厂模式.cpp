#include <iostream>
using namespace std;
// 意图：提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类。
class ProductA
{
public:
    virtual void show() = 0;
    virtual ~ProductA() = default;
};

class ProductB
{
public:
    virtual void show() = 0;
    virtual ~ProductB() = default;
};

class productA1 : public ProductA
{
public:
    void show() override
    {
        cout << "我是产品A1" << endl;
    }
    ~productA1() override
    {
        cout << "产品A1被销毁" << endl;
    }
};

class productA2 : public ProductA
{
public:
    void show() override
    {
        cout << "我是产品A2" << endl;
    }
    ~productA2() override
    {
        cout << "产品A2被销毁" << endl;
    }
};

class productB1 : public ProductB
{
public:
    void show() override
    {
        cout << "我是产品B1" << endl;
    }
    ~productB1() override
    {
        cout << "产品B1被销毁" << endl;
    }
};

class productB2 : public ProductB
{
public:
    void show() override
    {
        cout << "我是产品B2" << endl;
    }
    ~productB2() override
    {
        cout << "产品B2被销毁" << endl;
    }
};

class Factory
{
public:
    virtual ProductA *createProductA() = 0;
    virtual ProductB *createProductB() = 0;
};

class Factory1 : public Factory
{
public:
    ProductA *createProductA() override
    {
        return new productA1();
    }
    ProductB *createProductB() override
    {
        return new productB1();
    }
};

class Factory2 : public Factory
{
public:
    ProductA *createProductA() override
    {
        return new productA2();
    }
    ProductB *createProductB() override
    {
        return new productB2();
    }
};

// FactoryB类实现了完整的抽象工厂接口
class FactoryB : public Factory
{
public:
    ProductA *createProductA() override
    {
        // 可以返回nullptr或适当的默认实现
        return nullptr; // 或者抛出异常表示不支持创建ProductA
    }

    ProductB *createProductB() override
    {
        return new productB1();
    }
};

int main()
{
    Factory1 factory1;
    Factory2 factory2;
    ProductA *productA1 = factory1.createProductA();
    ProductB *productB1 = factory1.createProductB();
    ProductA *productA2 = factory2.createProductA();
    ProductB *productB2 = factory2.createProductB();
    productA1->show();
    productB1->show();
    productA2->show();
    productB2->show();
    delete productA1;
    delete productB1;
    delete productA2;
    delete productB2;
    productA1 = nullptr;
    productB1 = nullptr;
    productA2 = nullptr;
    productB2 = nullptr;

    return 0;
}