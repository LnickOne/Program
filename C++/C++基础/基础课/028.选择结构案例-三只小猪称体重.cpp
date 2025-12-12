#include <iostream>
using namespace std;

int main()
{
    // 三个小猪称体重，判断哪只小猪最重

    // 1、创建三只小猪的体重变量
    int A = 0;
    int B = 0;
    int C = 0;

    // 2、让用户输入三只小猪的体重
    cout << "请输入小猪A的体重：" << endl;
    cin >> A;

    cout << "请输入小猪B的体重：" << endl;
    cin >> B;

    cout << "请输入小猪C的体重：" << endl;
    cin >> C;

    cout << "小猪A的体重为：" << A << endl;
    cout << "小猪B的体重为：" << B << endl;
    cout << "小猪C的体重为：" << C << endl;

    // 3、判断三只哪只小猪最重
    // 先判断A和B重量
    if (A > B) // A比B重
    {
        if (A > C)
        {
            cout << "小猪A最重！" << endl;
        }
        else
        {
            cout << "小猪C最重！" << endl;
        }
    }
    else // B比A重
    {
        if (B > C)
        {
            cout << "小猪B最重！" << endl;
        }
        else
        {
            cout << "小猪C最重！" << endl;
        }
    }
    return 0;
}