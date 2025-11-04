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