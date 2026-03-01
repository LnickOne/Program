/*
给定一个二进制数组 nums 和一个整数 k，假设最多可以翻转 k 个 0 ，则返回执行操作后 数组中连续 1 的最大个数 。
示例 1：
输入：nums = [1,1,1,0,0,0,1,1,1,1,0], K = 2
输出：6
解释：[1,1,1,0,0,1,1,1,1,1,1]
粗体数字从 0 翻转到 1，最长的子数组长度为 6。
示例 2：
输入：nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], K = 3
输出：10
解释：[0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
粗体数字从 0 翻转到 1，最长的子数组长度为 10。
*/
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
    int longestOnes(vector<int> &nums, int k)
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
            while (count_0 > k)
            {
                if (nums[left] == 0)
                {
                    count_0 -= 1;
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
    vector<int> nums = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
    int k = 2;
    Solution s;
    int result = s.longestOnes(nums, k);
    cout << result << endl;
    nums = {0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1};
    k = 3;
    result = s.longestOnes(nums, k);
    cout << result << endl;
    return 0;
}