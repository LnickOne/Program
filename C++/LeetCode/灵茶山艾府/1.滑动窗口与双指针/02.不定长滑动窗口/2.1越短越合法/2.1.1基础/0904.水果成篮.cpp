/*
树用一个整数数组 fruits 表示，其中 fruits[i] 是第 i 棵树上的水果 种类 。
你想要尽可能多地收集水果。必须按照要求采摘水果：
你只有 两个 篮子，并且每个篮子只能装 单一类型 的水果。每个篮子能够装的水果总量没有限制。
你可以选择任意一棵树开始采摘，你必须从 每棵 树（包括开始采摘的树）上 恰好摘一个水果。
采摘的水果应当符合篮子中的水果类型。每采摘一次，你将会向右移动到下一棵树，并继续采摘。
一旦你走到某棵树前，但水果不符合篮子的水果类型，那么就必须停止采摘。
给你一个整数数组 fruits ，返回你可以收集的水果的 最大 数目。
示例 1：
输入：fruits = [1,2,1]
输出：3
解释：可以采摘全部 3 棵树。
示例 2：
输入：fruits = [0,1,2,2]
输出：3
解释：可以采摘 [1,2,2] 这三棵树。
如果从第一棵树开始采摘，则只能采摘 [0,1] 这两棵树。
示例 3：
输入：fruits = [1,2,3,2,2]
输出：4
解释：可以采摘 [2,3,2,2] 这四棵树。
如果从第一棵树开始采摘，则只能采摘 [1,2] 这两棵树。
示例 4：
输入：fruits = [3,3,3,1,2,1,1,2,3,3,4]
输出：5
解释：可以采摘 [1,2,1,1,2] 这五棵树。
*/
/*
解题思路
枚举子数组的右端点 right。同时用一个哈希表 cnt 维护子数组内每个元素的出现次数。
如果 fruits[right] 加入哈希表后，发现哈希表的大小超过了 2（篮子的数目），那么子数组不满足要求。
移动子数组的左端点 left，把 fruits[left] 的出现次数减一，直到哈希表中的元素种数等于 2。
如果fruits[left] 的出现次数变成0，需要从 cnt 中移除，表示子数组内少了一种元素。
如果不移除，我们无法通过 cnt 的大小判断窗口中的元素种数。
*/
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
class Solution
{
public:
    int totalFruit(vector<int> &fruits)
    {
        int result = 0;
        int basket = 2;
        unordered_map<int, int> fruitsMap;
        int left = 0;
        for (int right = 0; right < fruits.size(); right += 1)
        {
            fruitsMap[fruits[right]] += 1;
            while (fruitsMap.size() > basket)
            {
                fruitsMap[fruits[left]] -= 1;
                if (fruitsMap[fruits[left]] == 0)
                {
                    fruitsMap.erase(fruits[left]);
                }
                left += 1;
            }
            result = max(result, right - left + 1);
        }
        return result;
    }
};

int main()
{
    Solution s;
    vector<int> fruits_1 = {1, 2, 1};
    vector<int> fruits_2 = {0, 1, 2, 2};
    vector<int> fruits_3 = {1, 2, 3, 2, 2};
    vector<int> fruits_4 = {3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4};
    cout << s.totalFruit(fruits_1) << endl;
    cout << s.totalFruit(fruits_2) << endl;
    cout << s.totalFruit(fruits_3) << endl;
    cout << s.totalFruit(fruits_4) << endl;
    return 0;
}