/*
给你一个二进制数组 nums ，你需要从中删掉一个元素。
请你在删掉元素的结果数组中，返回最长的且只包含 1 的非空子数组的长度。
如果不存在这样的子数组，请返回 0 。

提示 1：
输入：nums = [1,1,0,1]
输出：3
解释：删掉位置 2 的数后，[1,1,1] 包含 3 个 1 。

示例 2：
输入：nums = [0,1,1,1,0,1,1,0,1]
输出：5
解释：删掉位置 4 的数字后，[0,1,1,1,1,1,0,1] 的最长全 1 子数组为 [1,1,1,1,1] 。

示例 3：
输入：nums = [1,1,1]
输出：2
解释：你必须要删除一个元素。

提示：
1 <= nums.length <= 105
nums[i] 要么是 0 要么是 1 。
*/
/*解题思路
删除后，子数组只有 1，也就是没有 0。那么删除之前呢？至多有一个 0。
所以问题相当于：
求最长子数组的长度（减一），满足子数组至多有一个 0。
子数组越短，包含的 0 越少，越能满足要求；子数组越长，包含的 0 越多，越无法满足要求。
所以当子数组的右端点增大时，左端点也随之增大（或者不变）
这个方法对于至多有 k 个 0 的题目，也是适用的。
注意：删除之前的子数组长度是 right−left+1，由于题目一定要删除一个数
（尤其是在全为 1 的情况下，一定要删除一个 1），
所以删除后的子数组长度是 right−left，用其更新答案的最大值。
*/
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
    int longestSubarray(vector<int> &nums)
    {
        int result = 0;
        int count_0 = 0;
        int left = 0;
        for (int right = 0; right < nums.size(); right += 1)
        {
            if (nums[right] == 0)
            {
                count_0 += 1;
            }
            while (count_0 > 1)
            {
                if (nums[left] == 0)
                {
                    count_0 -= 1;
                }
                left += 1;
            }
            result = max(result, right - left);
        }
        return result;
    }
};
int main()
{
    vector<int> nums = {1, 1, 0, 1};
    Solution s;
    int result = s.longestSubarray(nums);
    cout << result << endl;
    nums = {0, 1, 1, 1, 0, 1, 1, 0, 1};
    result = s.longestSubarray(nums);
    cout << result << endl;
    nums = {1, 1, 1};
    result = s.longestSubarray(nums);
    cout << result << endl;
    return 0;
}