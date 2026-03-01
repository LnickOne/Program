/*
给出一个二进制数组 data，你需要通过交换位置，将数组中 任何位置 上的 1组合到一起，并返回所有可能中所需 最少的交换次数。
示例 1:
输入: data = [1,0,1,0,1]
输出: 1
解释:
有三种可能的方法可以把所有的 1 组合在一起：
[1,1,1,0,0]，交换 1 次；
[0,1,1,1,0]，交换 2 次；
[0,0,1,1,1]，交换 1 次。
所以最少的交换次数为 1。
示例 2:
输入：data = [0,0,0,1,0]
输出：0
解释：由于数组中只有一个 1，所以不需要交换。
示例 3:
输入：data = [1,0,1,0,1,0,0,1,1,0,1]
输出：3
解释：
交换 3 次，一种可行的只用 3 次交换的解决方案是 [0,0,0,0,0,1,1,1,1,1,1]。
示例 4:
输入: data =[1,0,1,0,1,0,1,1,1,0,1,0,0,1,1,1,0,0,1,1,1,0,1,0,1,1,0,0,0,1,1,1,1,0,0,1]
输出:8
*/
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
    int minSwaps(vector<int> &data)
    {
        /*
        先统计数组中1的个数，记为k，然后使用滑动窗口，窗口大小为k，窗口右边界从左向右移动，统计窗口内1的个数，记为count_1。
        每次移动窗口时，都更新count_1的值，最后窗口右边界移动到数组末尾时，窗口内1的个数最多，记为最后答案为k-max
        */
        int k = 0;
        for (int &num : data)
        {
            if (num == 1)
                k += num;
        }
        int count_1 = 0;
        for (int i = 0; i < k; i += 1)
        {
            if (data[i] == 1)
                count_1 += data[i];
        }
        int max_change = count_1;
        for (int i = k; i < data.size(); i += 1)
        {
            count_1 += data[i];
            count_1 -= data[i - k];
            max_change = max(max_change, count_1);
        }
        return k - max_change;
    }
};
int main()
{
    return 0;
}