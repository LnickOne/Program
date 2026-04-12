# @lc app=leetcode.cn id=16 lang=python3
# [16] 最接近的三数之和
# https://leetcode.cn/problems/3sum-closest/description/
# algorithms
# Medium (44.83%)
# Likes:    1772
# Dislikes: 0
# Total Accepted:    670.5K
# Total Submissions: 1.5M
# Testcase Example:  '[-1,2,1,-4]\n1'
# 给你一个长度为 n 的整数数组 nums 和 一个目标值 target。请你从 nums 中选出三个整数，使它们的和与 target 最接近。
# 返回这三个数的和。
# 假定每组输入只存在恰好一个解。
# 示例 1：
# 输入：nums = [-1,2,1,-4], target = 1
# 输出：2
# 解释：与 target 最接近的和是 2 (-1 + 2 + 1 = 2)。
# 示例 2：
# 输入：nums = [0,0,0], target = 1
# 输出：0
# 解释：与 target 最接近的和是 0（0 + 0 + 0 = 0）。
# 提示：
# 3 <= nums.length <= 1000
# -1000 <= nums[i] <= 1000
# -10^4 <= target <= 10^4



# @lc code=start
from typing import List


class Solution:
    def threeSumClosest(self, nums: List[int], target: int) -> int:
        nums.sort()
        result = nums[0] + nums[1] + nums[2]
        for i in range(0, len(nums)):
            if i > 0 and nums[i - 1] == nums[i]:
                continue
            left, right = i + 1, len(nums) - 1
            while left < right:
                sum = nums[i] + nums[left] + nums[right]
                if sum == target:
                    return sum
                elif sum < target:
                    left += 1
                elif sum > target:
                    right -= 1
                if abs(result - target) > abs(sum - target):
                    result = sum
        return result


print(Solution().threeSumClosest([-1, 2, 1, -4], 1))
print(Solution().threeSumClosest([0, 0, 0], 1))
print(Solution().threeSumClosest([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10], 10))
print(Solution().threeSumClosest([-1, 2, 1, -4], 1))
print(Solution().threeSumClosest([-1, 2, 1, -4], 1))
# @lc code=end
