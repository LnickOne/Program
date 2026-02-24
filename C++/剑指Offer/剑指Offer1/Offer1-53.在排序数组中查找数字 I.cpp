/* > 题目难度: 简单

> [原题链接](https://leetcode-cn.com/problems/zai-pai-xu-shu-zu-zhong-cha-zhao-shu-zi-lcof/)

## 题目描述

统计一个数字在排序数组中出现的次数。

- 0 <= 数组长度 <= 50000

## 题目样例

### 示例

- 输入: nums = [5,7,7,8,8,10], target = 8
- 输出: 2

- 输入: nums = [5,7,7,8,8,10], target = 6
- 输出: 0

## 题目思考

1. 可以用小于 O(N)的时间复杂度得出结果吗?
2. 可以做到 O(1) 空间复杂度吗?

## 解决方案

#### 思路

- 一个比较容易想到的思路是使用一个计数字典, 遍历一遍数组统计每个数的出现次数, 最后返回 target 的次数. 但这样时间和空间复杂度都是 O(N), 也用不上题目中数组是排序的这一条件
- 如何利用排序这一条件统计数字出现次数呢? 我们可以尝试二分查找的思路, 分别找到该数字的左右边界对应的下标, 然后次数就是`右边界-左边界+1` (数组存在该数字的情况下)
  - 查找左边界: 如果找到等于 target 的数时, 需要继续往左找. 而如果数组中没有等于 target 的数, 则直接返回 None, 此时就知道该数字的出现次数为 0 了, 无需继续找右边界
  - 查找右边界: 如果找到等于 target 的数时, 需要继续往右找
- 注意可以将二分查找代码整合到一个方法中, 传入一个 flag 标记当前是找左边界还是右边界, 以减少代码冗余
- 下面代码对必要的步骤有详细的解释, 方便大家理解

#### 复杂度

- 时间复杂度 O(logN): 二分查找两次
- 空间复杂度 O(1): 只定义了几个变量

#### 代码

```python
class Solution:
    def search(self, nums: List[int], target: int) -> int:
        def binarySearch(isleft):
            # 传入flag isleft, 标记当前是查找左边界还是右边界
            s, e = 0, len(nums) - 1
            # 初始化结果为None
            res = None
            while s <= e:
                m = (s + e) >> 1
                if nums[m] == target:
                    if isleft:
                        # 当前查找的是左边界, 更新结果为等于target的更小的下标, 同时向左继续查找
                        res = m if res is None else min(res, m)
                        e = m - 1
                    else:
                        # 当前查找的是右边界, 更新结果为等于target的更大的下标, 同时向右继续查找
                        res = m if res is None else max(res, m)
                        s = m + 1
                elif nums[m] < target:
                    s = m + 1
                else:
                    e = m - 1
            return res

        left = binarySearch(True)
        if left is None:
            # 如果左边界不存在, 则说明整个数组没有target, 直接返回0
            return 0
        right = binarySearch(False)
        # 最终结果就是右边界-左边界+1
        return right - left + 1
```

---

 */