/*
> 题目难度: 简单
> [原题链接](https://leetcode-cn.com/problems/ti-huan-kong-ge-lcof/)
 题目描述
请实现一个函数，把字符串 s 中的每个空格替换成`"%20"`。
0 <= s 的长度 <= 10000
 题目样例
示例
输入
`s = "We are happy."`
输出
`"We%20are%20happy."`
 题目思考
分析
- 需要将空格转成`%20`, 理论上只需要遍历一遍字符串, 直接转换即可
- 需要注意的是原来空格是一位字符, 转换后的是 3 个字符, 这就意味着如果需要遍历字符串的话, 原始字符串和目标字符串的下标不相同
实现
1. 利用语言特性
   - 大部分高级语言都提供了 split 和 join
   - 所以我们只需要按照空格作为分隔符将字符串 split 成字符串数组
   - 最后再用`%20`作为分隔符 join 起来即可
2. 利用 string 操作
   - 我们完全可以新建一个初始为空的目标字符串
   - 然后直接遍历原始字符串: 遇到空格追加`%20`; 而遇到其他字符直接追加字符本身即可
3. 利用字符数组
   - 这种方案更适用于类似 C 语言这种提供原地修改功能的字符数组, python 的话就需要使用 list 存字符来模拟了, 最后再 join 得到字符串
   - 首先遍历原始字符串, 统计空格的数目`blankcnt`
   - 然后申请一个长度为`blankcnt * 3 + (len - blankcnt)`长度的字符数组 (因为空格的长度要变为原来的 3 倍, 其他字符长度保持不变)
   - 最后维护两个下标同时遍历即可: 遇到普通字符按原样复制, 两下标都+1; 而遇到空格则依次填入`%`,`2`,`0`, 原始下标+1, 新下标+3

复杂度
- 时间复杂度 `O(N)`
  - 只需要遍历一遍或两遍字符串
- 空间复杂度 `O(N)`
  - 结果字符串至少需要有 N 个字符
*/
#include <string>
#include <iostream>
using namespace std;
class Solution
{
public:
    string pathEncryption(string path)
    {
        for (char &ch : path)
        {
            if (ch == '.')
            {
                ch = ' ';
            }
        }
        return path;
    }
};

int main()
{
    Solution s;
    string path = "a.b.c";
    cout << s.pathEncryption(path) << endl;
    return 0;
}