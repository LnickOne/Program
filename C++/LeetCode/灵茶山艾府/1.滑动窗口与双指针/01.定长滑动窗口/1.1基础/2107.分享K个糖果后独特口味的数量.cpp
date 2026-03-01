/*
您将获得一个 从0开始的 整数数组 candies ，其中 candies[i] 表示第 i个糖果的味道。
你妈妈想让你和你妹妹分享这些糖果，给她 k 个 连续的糖果，但你想保留尽可能多的糖果口味。
在与妹妹分享后，返回 最多 可保留的 独特口味的糖果。

示例 1：
输入: candies = [1,2,2,3,4,3], k = 3
输出: 3
解释:
将[1,3]（含[2,2,3]）范围内的糖果加入[2,2,3]口味。
你可以吃各种口味的糖果[1,4,3]。有3种独特的口味，所以返回3。

示例 2:
输入: candies = [2,2,2,2,3,3], k = 2
输出: 2
解释:
在[3,4]范围内（含[2,3]）的糖果中加入[2,3]口味。
你可以吃各种口味的糖果[2,2,2,3]。
有两种独特的口味，所以返回2。
请注意，你也可以分享口味为[2,2]的糖果，吃口味为[2,2,3,3]的糖果。

示例 3:
输入: candies = [2,4,5], k = 0
输出: 3
解释:
你不必给任何糖果。你可以吃各种口味的糖果[2,4,5]。有3种独特的口味，所以返回3。
*/
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
class Solution
{
public:
    int shareCandies(vector<int> &candies, int k)
    {
        unordered_map<int, int> cnt;
        for (int num : candies)
        {
            cnt[num] += 1;
        }
        if (k == 0) // 不发糖果给妹妹，自己吃到全部糖果
            return cnt.size();
        int result = 0;
        // 当前剩余的独特口味数量
        int uniqueCount = cnt.size();
        // 处理第一个窗口，窗口移动代表发糖果给妹妹
        for (int i = 0; i < k; i += 1)
        {
            cnt[candies[i]] -= 1;
            if (cnt[candies[i]] == 0)
            {
                uniqueCount -= 1; // 如果某个口味的糖果数量变为0，减少独特口味计数
            }
        }
        // 记录第一个窗口的结果
        result = uniqueCount;
        // 处理后续窗口
        for (int i = k; i < candies.size(); i++)
        {
            cnt[candies[i]] -= 1;
            cnt[candies[i - k]] += 1;
            // 如果窗口前移动(这个口味从1减少到0，减少独特口味计数
            if (cnt[candies[i]] == 0)
            {
                uniqueCount -= 1;
            }
            // 如果这个糖果数量从0增加到1，增加独特口味计数
            if (cnt[candies[i - k]] == 1)
            {
                uniqueCount += 1;
            }
            result = max(result, uniqueCount);
        }

        return result;
    }
};
int main()
{
    Solution s;
    vector<int> candies = {1, 2, 2, 3, 4, 3};
    int k = 3;
    cout << s.shareCandies(candies, k) << endl;
    candies = {2, 2, 2, 2, 3, 3};
    k = 2;
    cout << s.shareCandies(candies, k) << endl;
    candies = {2, 4, 5};
    k = 0;
    cout << s.shareCandies(candies, k) << endl;
    return 0;
}