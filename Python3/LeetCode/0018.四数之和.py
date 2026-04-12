# @lc app=leetcode.cn id=18 lang=python3
# [18] 四数之和
# https://leetcode.cn/problems/4sum/description/
# algorithms
# Medium (36.92%)
# Likes:    2165
# Dislikes: 0
# Total Accepted:    783K
# Total Submissions: 2.1M
# Testcase Example:  '[1,0,-1,0,-2,2]\n0'
# 给你一个由 n 个整数组成的数组 nums ，和一个目标值 target 。请你找出并返回满足下述全部条件且不重复的四元组 [nums[a],
# nums[b], nums[c], nums[d]] （若两个四元组元素一一对应，则认为两个四元组重复）：
# 0 <= a, b, c, d < n
# a、b、c 和 d 互不相同
# nums[a] + nums[b] + nums[c] + nums[d] == target
# 你可以按 任意顺序 返回答案 。
# 示例 1：
# 输入：nums = [1,0,-1,0,-2,2], target = 0
# 输出：[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
# 示例 2：
# 输入：nums = [2,2,2,2,2], target = 8
# 输出：[[2,2,2,2]]
# 提示：
# 1 <= nums.length <= 200
# -10^9 <= nums[i] <= 10^9
# -10^9 <= target <= 10^9
# @lc code=start
from typing import List


class Solution:
    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
        nums.sort()
        result = []
        for i in range(len(nums)):
            if i > 0 and nums[i] == nums[i - 1]:
                continue
            for j in range(i + 1, len(nums)):
                if j > i + 1 and nums[j] == nums[j - 1]:
                    continue
                left, right = j + 1, len(nums) - 1
                while left < right:
                    sum = nums[i] + nums[j] + nums[left] + nums[right]
                    if sum == target:
                        result.append([nums[i], nums[j], nums[left], nums[right]])
                        while left < right and nums[left] == nums[left + 1]:
                            left += 1
                        while left < right and nums[right] == nums[right - 1]:
                            right -= 1
                        left += 1
                        right -= 1
                    elif sum > target:
                        right -= 1
                    elif sum < target:
                        left += 1
        return result


print(Solution().fourSum([1, 0, -1, 0, -2, 2], 0))
print(Solution().fourSum([2, 2, 2, 2, 2], 8))
print(Solution().fourSum([-3, -2, -1, 0, 0, 1, 2, 3], 0))
# @lc code=end
