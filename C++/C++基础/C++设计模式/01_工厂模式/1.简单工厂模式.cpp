#include <iostream>
#include <string>
#include <thread>
using namespace std;
//违反开放-关闭原则
class Product
{
public:
    virtual void show() = 0;
    virtual ~Product()
    {
        cout << "产品被销毁" << endl;
    }
};

class productA : public Product
{
public:
    void show() override
    {
        cout << "我是产品A" << endl;
    }
};

class productB : public Product
{
public:
    void show() override
    {
        cout << "我是产品B" << endl;
    }
};
class Factory
{
public:
    static Product *createProduct(string type)
    {
        Product *product = nullptr;
        if (type == "A")
        {
            product = new productA();
        }
        else if (type == "B")
        {
            product = new productB();
        }
        else
        {
            cout << "没有该类型的产品" + type << endl;
        }
        return product;
    }
};
int main()
{
    // 使用静态方法创建产品
    Product *productA = Factory::createProduct("A");
    // 不使用静态方法创建产品
    Factory factory;
    Product *productB = factory.createProduct("B");
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