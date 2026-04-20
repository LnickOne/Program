# @lc app=leetcode.cn id=4 lang=python3
# [4] 寻找两个正序数组的中位数
# @lc code=start
from typing import List


class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        nums = nums1 + nums2
        nums.sort()
        if len(nums) % 2 == 0:
            return (nums[len(nums) // 2 - 1] + nums[len(nums) // 2]) / 2
        else:
            return nums[len(nums) // 2]


print(Solution().findMedianSortedArrays([1, 3], [2]))
print(Solution().findMedianSortedArrays([1, 2], [3, 4]))
print(Solution().findMedianSortedArrays([0, 0], [0, 0]))
print(Solution().findMedianSortedArrays([1, 2], [3, 4, 5]))

# @lc code=end
