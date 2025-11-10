#include <iostream>
using namespace std;

int main()
{
    int score = 0;
    cout << "请输入考试分数：" << endl;
    cin >> score;

    if (score > 600)
    {
        cout << "我考上了一本大学!" << endl;
        if (score > 700)
        {
            cout << "我考上了北大!" << endl;
        }
        else if (score > 650)
        {
            cout << "我考上了清华!" << endl;
        }
        else
        {
            cout << "我考上了人大!" << endl;
        }
    }
    else if (score > 500)
    {
        cout << "我考上了二本大学!" << endl;
    }
    else if (score > 400)
    {
        cout << "我考上了三本大学!" << endl;
    }
    else
    {
        cout << "我未考上本科!" << endl;
    }

    system("pause");
    return 0;
}