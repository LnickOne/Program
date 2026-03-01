/*
给你一个下标从 0 开始 的整数数组 nums ，其中 nums[i] 表示第 i 名学生的分数。
另给你一个整数 k 。从数组中选出任意 k 名学生的分数，使这 k 个分数间 最高分 和最低分 的 差值 达到 最小化 。
返回可能的 最小差值 。

示例 1：
输入：nums = [90], k = 1
输出：0
解释：选出 1 名学生的分数，仅有 1 种方法：
- [90] 最高分和最低分之间的差值是 90 - 90 = 0
可能的最小差值是 0

示例 2：
输入：nums = [9,4,1,7], k = 2
输出：2
解释：选出 2 名学生的分数，有 6 种方法：
- [9,4,1,7] 最高分和最低分之间的差值是 9 - 4 = 5
- [9,4,1,7] 最高分和最低分之间的差值是 9 - 1 = 8
- [9,4,1,7] 最高分和最低分之间的差值是 9 - 7 = 2
- [9,4,1,7] 最高分和最低分之间的差值是 4 - 1 = 3
- [9,4,1,7] 最高分和最低分之间的差值是 7 - 4 = 3
- [9,4,1,7] 最高分和最低分之间的差值是 7 - 1 = 6
可能的最小差值是 2
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
class Solution
{
public:
    int minimumDifference(vector<int> &nums, int k)
    {
        int result = INT_MAX;
        sort(nums.begin(), nums.end());
        for (int i = 0; i + k - 1 < nums.size(); i += 1)
        {
            result = min(result, nums[i + k - 1] - nums[i]);
        }
        return result;
    }
};
int main()
{
    Solution s;
    vector<int> nums1 = {9, 4, 1, 7};
    int k = 2;
    cout << s.minimumDifference(nums1, k) << endl;
    vector<int> nums2 = {90};
    k = 1;
    cout << s.minimumDifference(nums2, k) << endl;
    vector<int> nums3 = {9, 4, 1, 7};
    k = 3;
    cout << s.minimumDifference(nums3, k) << endl;
    return 0;
}