#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 意图：将一个复杂对象的构建与它的表示分离，使得同样的构建过程可以创建不同的表示。
/*
 1.Builder为创建一个复杂对象的接口，
 2.ConcreteBuilder为具体的创建者，实现Builder的接口，
 3.Director为指挥者，
 4.Product为产品，
 5.客户端通过指挥者和具体创建者来创建产品。
*/
//总结：具体的生成器生成不同的产品，根据不同的需求来构建产品的不同部分。
class Product
{
public:
    vector<string> parts;
    void Show()
    {
        for (auto part : parts)
        {
            cout << "产品的组成: " << part << endl;
        }
    }
};
class Builder
{
public:
    virtual void BuildPart() = 0;
    virtual Product *GetProduct() = 0;
};

class Build1 : public Builder
{
    Product *product = new Product();
public:
    void BuildPart() override
    {
        product->parts.push_back("部件A");
        product->parts.push_back("部件B");
        product->parts.push_back("部件C");
        product->parts.push_back("部件D");
        product->parts.push_back("部件E");
        product->parts.push_back("部件F");
    }
    Product *GetProduct() override
    {
        return product;
    }
};
class Build2 : public Builder
{
    Product *product = new Product();
public:
    void BuildPart() override
    {
        product->parts.push_back("部件A");
        product->parts.push_back("部件B");
        product->parts.push_back("部件C");
    }
    Product *GetProduct() override
    {
        return product;
    }
};

class Director
{
public:
    void Construct(Builder *builder)
    {
        builder->BuildPart();
    }
};

int main()
{
    Director director;
    Build1 build1;
    director.Construct(&build1);
    Product *product1 = build1.GetProduct();
    product1->Show();
    // Build2 build2;
    // director.Construct(&build2);
    // Product *product2 = build2.GetProduct();
    // product2->Show();
    // return 0;
}