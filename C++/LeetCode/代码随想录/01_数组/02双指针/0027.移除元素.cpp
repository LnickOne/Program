/*
给你一个按非递减顺序排序的整数数组nums，返回每个数字的平方组成的新数组，要求也按非递减顺序排序。
示例 1：
输入：nums = [-4,-1,0,3,10]
输出：[0,1,9,16,100]
解释：平方后，数组变为 [16,1,0,9,100]
排序后，数组变为 [0,1,9,16,100]
示例 2：
输入：nums = [-7,-3,2,3,11]
输出：[4,9,9,49,121]
*/
#include <vector>
#include <iostream>
using namespace std;
class Solution
{
public:
    int removeElement(vector<int> &nums, const int val)
    {
        // 双指针法（快慢指针法）： 通过一个快指针和慢指针在一个for循环下完成两个for循环的工作。
        int result = 0;
        int slow = 0;
        for (int fast = 0; fast < nums.size(); ++fast)
        {
            if (nums[fast] != val)
            {
                nums[slow] = nums[fast];
                slow += 1;
            }
        }
        return slow;
    }
};

int main()
{
    vector<int> nums_1 = {3, 2, 2, 3};
    vector<int> nums_2 = {0, 1, 2, 2, 3, 0, 4, 2};
    int val_1 = 3;
    int val_2 = 2;
    Solution s;
    cout << s.removeElement(nums_2, val_2) << endl;
    for (const auto &i : nums_2)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}