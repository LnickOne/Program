/*
> 题目难度: 简单

> [原题链接](https://leetcode-cn.com/problems/bao-han-minhan-shu-de-zhan-lcof/)

> 今天继续更新剑指 offer 系列, 这道题太经典了, 做过的同学可以复习下, 没做过的同学也可以先思考下怎么做~

> 老样子**晚上 6 点 45 分**准时更新公众号 **每日精选算法题**, 大家记得关注哦~ 另外在公众号里回复 **offer** 就能看到剑指 offer 系列当前连载的所有文章了

## 题目描述

定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的 min 函数在该栈中，调用 min、push 及 pop 的时间复杂度都是 O(1)。

各函数的调用总次数不超过 20000 次

## 题目样例

### 示例

```
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.min();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.min();   --> 返回 -2.
```

## 题目思考

1. 内部需要什么数据结构来满足所有操作都是 O(1), 一个栈够吗?

## 解决方案

### 思路

- 要使得 push 和 pop 的复杂度为 O(1), 传统的栈就可以搞定, 难点在于如何使得 min 函数也为 O(1)
- 如果我们能一直维护当前所有元素的最小值, 那么 min 函数直接返回它就可以, 但问题是在 pop 的时候有可能会正好 pop 这个最小值, pop 之后的最小值(也即原来的次小值)如何得到呢?
- 要存储多个最小值, 显然一个变量不够用. 而根据上一步的分析, 这里我们可以考虑额外引入一个**单调递减栈**, 栈顶存当前最小值, 下面依次是次小, 第三小...
- 这样如果 pop 了最小值的话, 这个单调栈的栈顶仍会保存 pop 后的最小值, 每次 min 只需要取这个栈的栈顶即可
- 而 push 的时候也需要额外的操作, 由于是单调栈, 只需要在新的值**小于等于**栈顶的时候才 push 到单调栈中.特别注意在等于栈顶的时候也要 push 到单调栈中, 这是因为如果对于重复的最小值 x 不 push, 那么在后续的 pop 其中一个 x 之后, 栈顶(不再是 x)就和实际最小值(仍为 x)不一致了

### 复杂度

- 时间复杂度 `O(1)`
  - 各种操作都是常数复杂度
- 空间复杂度 `O(N)`
  - 使用了两个栈

### 代码

```python
class MinStack:
    def __init__(self):
        """
        initialize your data structure here.
        """
        # 一个普通栈和一个单调递减栈
        self.minstack = []
        self.stack = []

    def push(self, x: int) -> None:
        self.stack.append(x)
        if not self.minstack or x <= self.minstack[-1]:
            # 如果单调栈顶为空或者当前新值小于等于单调栈顶才push
            # 注意这里等于也需要push. 如果对于重复的最小值 x 不 push, 那么在后续的 pop 其中一个 x 之后, 栈顶(不再是 x)就和实际最小值(仍为 x)不一致了
            self.minstack.append(x)

    def pop(self) -> None:
        if not self.stack:
            return
        x = self.stack.pop()
        if x == self.minstack[-1]:
            # 如果单调栈顶恰好等于pop的值, 也要pop单调栈
            self.minstack.pop()

    def top(self) -> int:
        if not self.stack:
            return -1
        return self.stack[-1]

    def min(self) -> int:
        if not self.minstack:
            return -1
        return self.minstack[-1]
```

---
*/
