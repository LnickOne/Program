/* > 题目难度: 简单

> [原题链接](https://leetcode-cn.com/problems/da-yin-cong-1dao-zui-da-de-nwei-shu-lcof/)

## 题目描述

输入数字 n，按顺序打印出从 1 到最大的 n 位十进制数。比如输入 3，则打印出 1、2、3 一直到最大的 3 位数 999。

- 用返回一个整数列表来代替打印
- n 为正整数

## 题目样例

### 示例

#### 输入

1

#### 输出

[1,2,3,4,5,6,7,8,9]

## 题目思考

1. 如何得到最大值?

## 解决方案

### 思路

#### 分析

- 题目很直白, 我们只需要得到 n 位数的上限, 将其作为循环终点, 从 1 开始循环依次保存到数组即可

#### 实现

1. 方案 1: 取上限的下一个数, 显然是 `pow(10, n)`, 循环上界小于它即可
2. 方案 2: 直接取上限, n 位数的上限就是 **n 个 9**, 通过字符串转换可以直接得到
3. 方案 3: 还是直接取上限, 通过将当前数字乘以 10 然后加 9 的方式循环生成上限

### 复杂度

- 时间复杂度 `O(10^N)`
  - 需要循环到 `10^N` 依次输出
- 空间复杂度 `O(1)`
  - 只使用了几个变量

### 代码

#### 方案 1 - 取上限的下一个数

```python
class Solution:
    def printNumbers(self, n: int) -> List[int]:
        return list(range(1, 10**n))
```

#### 方案 2 - 利用字符串转换取上限数

```python
class Solution:
    def printNumbers(self, n: int) -> List[int]:
        mx = int("9" * n)
        res = []
        for i in range(1, mx + 1):
            res.append(i)
        return res
```

#### 方案 3 - 利用循环求上限数

```python
class Solution:
    def printNumbers(self, n: int) -> List[int]:
        mx = 0
        for i in range(n):
            mx = mx * 10 + 9
        res = []
        for i in range(1, mx + 1):
            res.append(i)
        return res
```

---
 */