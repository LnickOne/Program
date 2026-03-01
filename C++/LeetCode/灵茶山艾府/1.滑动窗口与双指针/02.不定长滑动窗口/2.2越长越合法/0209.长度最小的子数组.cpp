/*
  所谓滑动窗口，就是不断的调节子序列的起始位置和终止位置，从而得出我们要想的结果。
  在暴力解法中，是一个for循环滑动窗口的起始位置，一个for循环为滑动窗口的终止位置，用两个for循环完成了一个不断搜索区间的过程。
  那么滑动窗口如何用一个for循环来完成这个操作呢。
  首先要思考 如果用一个for循环，那么应该表示滑动窗口的起始位置，还是终止位置。
  如果只用一个for循环来表示滑动窗口的起始位置，那么如何遍历剩下的终止位置？ 此时难免再次陷入暴力解法的怪圈。
  所以 只用一个for循环，那么这个循环的索引，一定是表示滑动窗口的终止位置。
  那么问题来了， 滑动窗口的起始位置如何移动呢？
  这里还是以题目中的示例来举例，s=7， 数组是2，3，1，2，4，3，来看一下查找的过程： 最后找到 4，3 是最短距离。
  其实从动画中可以发现滑动窗口也可以理解为双指针法的一种！只不过这种解法更像是一个窗口的移动，所以叫做滑动窗口更适合一些。
  在本题中实现滑动窗口，主要确定如下三点：
  窗口内是什么？
  如何移动窗口的起始位置？
  如何移动窗口的结束位置？
  窗口就是 满足其和 ≥ s 的长度最小的 连续 子数组
  窗口的起始位置如何移动：如果当前窗口的值大于等于s了，窗口就要向前移动了（也就是该缩小了）。
  窗口的结束位置如何移动：窗口的结束位置就是遍历数组的指针，也就是for循环里的索引
  解题的关键在于 窗口的起始位置如何移动，如图所示：
  在本题中实现滑动窗口，主要确定如下三点：
  窗口内是什么？
  如何移动窗口的起始位置？
  如何移动窗口的结束位置？
  窗口就是 满足其和 ≥ s 的长度最小的 连续 子数组。
  窗口的起始位置如何移动：如果当前窗口的值大于等于s了，窗口就要向前移动了（也就是该缩小了）。
  窗口的结束位置如何移动：窗口的结束位置就是遍历数组的指针，也就是for循环里的索引。
*/
/*
给定一个含有 n 个正整数的数组和一个正整数 target 。
找出该数组中满足其总和大于等于 target 的长度最小的
子数组[numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。
 如果不存在符合条件的子数组，返回 0 。
示例 1：
输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。
示例 2：
输入：target = 4, nums = [1,4,4]
输出：1
示例 3：
输入：target = 11, nums = [1,1,1,1,1,1,1,1]
输出：0
*/
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  int minSubArrayLen(int target, vector<int> &nums)
  {
    return 0;
  }
};

int main()
{
  vector<int> nums_1 = {2, 3, 1, 2, 4, 3};
  vector<int> nums_2 = {1, 4, 4};
  vector<int> nums_3 = {1, 1, 1, 1, 1, 1, 1, 1};
  vector<int> nums_4 = {1, 2, 3, 4, 5};
  int target_1 = 7;
  int target_2 = 4;
  int target_3 = 11;
  int target_4 = 11;
  cout << Solution().minSubArrayLen(target_1, nums_1) << endl;
  cout << Solution().minSubArrayLen(target_2, nums_2) << endl;
  cout << Solution().minSubArrayLen(target_3, nums_3) << endl;
  cout << Solution().minSubArrayLen(target_4, nums_4) << endl;
  return 0;
}