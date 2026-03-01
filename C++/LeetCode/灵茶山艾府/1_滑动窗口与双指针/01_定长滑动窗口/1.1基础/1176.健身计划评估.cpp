/*
有一份计划消耗的卡路里表，其中 calories[i] 给出了第 i 天需要消耗的卡路里总量。
为了更好地评估这份计划，对于卡路里表中的每一天，你都需要计算他 「这一天以及之后的连续几天」 （共 k 天）内消耗的总卡路里 T：
如果 T < lower，那么这份计划相对糟糕，并失去 1 分；
如果 T > upper，那么这份计划相对优秀，并获得 1 分；
否则，这份计划普普通通，分值不做变动。
请返回统计完所有 calories.length 天后得到的总分作为评估结果。
注意：总分可能是负数。
示例 1：
输入：calories = [1,2,3,4,5], k = 1, lower = 3, upper = 3
输出：0
解释：calories[0], calories[1] < lower 而 calories[3], calories[4] > upper, 总分 = 0.
示例 2：
输入：calories = [3,2], k = 2, lower = 0, upper = 1
输出：1
解释：calories[0] + calories[1] > upper, 总分 = 1.
示例 3：
输入：calories = [6,5,0,0], k = 2, lower = 1, upper = 5
输出：0
解释：calories[0] + calories[1] > upper, calories[2] + calories[3] < lower, 总分 = 0.
*/
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
    int dietPlanPerformance(vector<int> &calories, int k, int lower, int upper)
    {
        int result = 0;
        int total = 0;
        // 处理第一个窗口
        for (int i = 0; i < k; i += 1)
        {
            total += calories[i];
        }
        if (total < lower)
            result -= 1;
        else if (total > upper)
            result += 1;
        // 处理后续窗口
        for (int i = k; i < calories.size(); i += 1)
        {
            total += calories[i];
            total -= calories[i - k];
            if (total < lower)
                result -= 1;
            else if (total > upper)
                result += 1;
        }
        return result;
    }
};
int main()
{
    // 测试用例
    vector<int> arr1 = {1, 2, 3, 4, 5};
    Solution s;
    int res1 = s.dietPlanPerformance(arr1, 1, 3, 3);
    cout << res1 << endl;
    vector<int> arr2 = {3, 2};
    int res2 = s.dietPlanPerformance(arr2, 2, 0, 1);
    cout << res2 << endl;
    vector<int> arr3 = {6, 5, 0, 0};
    int res3 = s.dietPlanPerformance(arr3, 2, 1, 5);
    cout << res3 << endl;
    return 0;
}