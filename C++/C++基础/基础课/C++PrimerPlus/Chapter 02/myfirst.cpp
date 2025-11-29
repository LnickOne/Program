// myfirst.cpp--显示一条消息

#include <iostream>                          // 预处理器指令
int main()                                   // 函数头
{                                            // 函数体开始
    using namespace std;                     // 使定义可见
    cout << "Come up and C++ me some time."; // 输出消息
    cout << endl;                            // 开始新行
    cout << "You won't regret it!" << endl;  // 更多输出
                                             // 如果输出窗口在您阅读前关闭，
                                             // 添加以下代码：
    // cout << "按任意键继续。" <<endl;
    // cin.get();
    return 0; // 终止main()函数
} // 函数体结束
