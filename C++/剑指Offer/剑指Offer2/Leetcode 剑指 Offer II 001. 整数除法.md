 题目难度: 简单

> [原题链接](https://leetcode.cn/problems/xoh6Oh/)

## 题目描述

- 给定两个整数 a 和 b ，求它们的除法的商 a/b ，要求不得使用乘号 '\*'、除号 '/' 以及求余符号 '%' 。
- 注意：
  - 整数除法的结果应当截去（truncate）其小数部分，例如：truncate(8.345) = 8 以及 truncate(-2.7335) = -2
  - 假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−2^31, 2^31−1]。本题中，如果除法结果溢出，则返回 2^31 − 1

### 示例 1：

- 输入：a = 15, b = 2
- 输出：7
- 解释：15/2 = truncate(7.5) = 7

### 示例 2：

- 输入：a = 7, b = -3
- 输出：-2
- 解释：7/-3 = truncate(-2.33333..) = -2

### 示例 3：

- 输入：a = 0, b = 1
- 输出：0

### 示例 4：

- 输入：a = 1, b = 1
- 输出：1

### 提示:

- -2^31 <= a, b <= 2^31 - 1
- b != 0

## 题目思考

1. 除法的本质是什么?
2. 可以利用哪些其他操作符?

## 解决方案

### 思路

- 分析题目, 一个直观的思路就是用减法代替除法: 循环减去除数并计数, 直到被除数小于除数为止, 最终计数就是商
- 但这种方法复杂度跟商的大小成正比, 假设被除数是 2^31, 除数是 2, 那就要循环 2^30 次, 效率过低, 有没有其他更高效的做法呢?
- 回顾题目要求, 它只是禁用了乘除和取模, 那除了四则运算, 我们程序员经常用到的还有位运算符, 以及它们的好伙伴: 二进制
- 回想二进制的性质, 我们的商转成二进制的话就相当于若干个位是 1, 然后其余位是 0
- 那么商就可以表示为多个 2 的幂的和, 例如 `12(0b1100)`, 就相当于 `8(0b1000)+4(0b0100)`
- 这样我们在进行除法的时候, 就可以不断循环, 进而将商分解, 例如 `128/3` 可以分解为 `3*(32+8+2)`, 即 `3*42`
- 具体做法就是初始化当前 2 的幂为 1, 并将它与除数的乘积初始化为除数, 然后将 2 的幂和除数乘积不断左移, 模拟乘 2, 直到除数乘积最接近且小于等于被除数为止
- 此时得到的 2 的幂就可以累加到最终的商里面了, 然后将被除数减去得到的除数乘积, 继续开启新一轮的循环, 直到最终被除数小于原始除数为止
- 另外根据题目要求, 还需要额外处理正负号以及数字范围
- 下面代码中对上面提到的每个步骤都有详细注释, 方便大家理解

### 复杂度

- 时间复杂度 O(logA): 每次循环只需要 A 的对数时间, 然后只会循环常数次
- 空间复杂度 O(1): 只使用了几个常数空间的变量

### 代码

```python
class Solution:
    def divide(self, dividend: int, divisor: int) -> int:
        # 核心思路: 2的幂和除数乘积不断左移一位, 直到最接近且小于等于被除数, 循环该过程直到被除数<除数
        # 先将数字都转为正数, 并记录商的符号
        neg = False
        if dividend < 0:
            dividend = -dividend
            neg = not neg
        if divisor < 0:
            divisor = -divisor
            neg = not neg
        res = 0
        # 注意循环条件是大于等于, 因为等于情况下仍有商, 为1
        while dividend >= divisor:
            # 2的幂初始化为1
            mi = 1
            # 除数乘积初始化为除数
            cur = divisor
            # 注意循环条件是大于等于, 相等时表示恰好整除
            while dividend >= (cur << 1):
                # 2的幂和除数乘积不断左移一位, 直到最接近且小于等于被除数
                cur <<= 1
                mi <<= 1
            # 此时的除数乘积就是最接近且小于等于被除数的数了
            # 商加上当前的2的幂
            res += mi
            # 被除数减去已经使用的除数乘积
            dividend -= cur
        # 恢复符号
        if neg:
            # 负号时需要取相反数
            res = -res
        # 注意溢出时取最大正数
        mn, mx = -(2**31), 2**31 - 1
        if res < mn or res > mx:
            return mx
        return res
```c++
#include <iostream>   // 添加输入输出流头文件
#include <climits>    // 已包含，用于INT_MIN/INT_MAX
using namespace std;  // 添加命名空间声明

class Solution {
public:
    int divide(int dividend, int divisor) {
        // 处理特殊情况：防止溢出
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }
        
        // 确定结果的符号
        bool neg = (dividend < 0) ^ (divisor < 0);
        
        // 使用long long避免溢出
        long long dvd = llabs((long long)dividend);
        long long dvs = llabs((long long)divisor);
        
        int res = 0;
        
        // 注意循环条件是大于等于, 因为等于情况下仍有商, 为1
        while (dvd >= dvs) {
            // 2的幂初始化为1
            long long mi = 1;
            // 除数乘积初始化为除数
            long long cur = dvs;
            
            // 注意循环条件是大于等于, 相等时表示恰好整除
            while (dvd >= (cur << 1)) {
                // 2的幂和除数乘积不断左移一位, 直到最接近且小于等于被除数
                cur <<= 1;
                mi <<= 1;
            }
            
            // 商加上当前的2的幂
            res += mi;
            // 被除数减去已经使用的除数乘积
            dvd -= cur;
        }
        
        // 恢复符号
        return neg ? -res : res;
    }
};
int main(){
    Solution s;
    int dividend = 15;
    int divisor = 2;
    int result = s.divide(dividend, divisor);
    cout << "Result: " << result << endl;  // 修复转义字符 &quot; 为 "
    return 0;
}
```