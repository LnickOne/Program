# @lc app=leetcode.cn id=2 lang=python3
# [2] 两数相加
# https://leetcode.cn/problems/add-two-numbers/description/
# algorithms
# Medium (46.67%)
# Likes:    11922
# Dislikes: 0
# Total Accepted:    2.8M
# Total Submissions: 6M
# Testcase Example:  '[2,4,3]\n[5,6,4]'
# 给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
# 请你将两个数相加，并以相同形式返回一个表示和的链表。
# 你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
# 示例 1：
# 输入：l1 = [2,4,3], l2 = [5,6,4]
# 输出：[7,0,8]
# 解释：342 + 465 = 807.
# 示例 2：
# 输入：l1 = [0], l2 = [0]
# 输出：[0]
# 示例 3：
# 输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
# 输出：[8,9,9,9,0,0,0,1]
# 提示：
# 每个链表中的节点数在范围 [1, 100] 内
# 0 <= Node.val <= 9
# 题目数据保证列表表示的数字不含前导零
# @lc code=start
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
from typing import Optional


class ListNode:
    def __init__(self, val, next=None):
        self.val = val
        self.next = next


def printListNode(head):
    temp = head
    while temp:
        print(temp.val, end=" ")
        temp = temp.next
    print()


class Solution:
    def addTwoNumbers(
        self, l1: Optional[ListNode], l2: Optional[ListNode]
    ) -> Optional[ListNode]:
        dummy = ListNode(0, None)
        cur = dummy
        sum = 0
        quotient = 0
        remainder = 0
        carry = 0
        while l1 and l2:
            sum = l1.val + l2.val + carry
            quotient = sum // 10
            remainder = sum % 10
            carry = quotient
            cur.next = ListNode(remainder, None)
            cur = cur.next
            l1 = l1.next
            l2 = l2.next
        while l1:
            sum = l1.val + carry
            quotient = sum // 10
            remainder = sum % 10
            carry = quotient
            cur.next = ListNode(remainder, None)
            cur = cur.next
            l1 = l1.next
        while l2:
            sum = l2.val + carry
            quotient = sum // 10
            remainder = sum % 10
            carry = quotient
            cur.next = ListNode(remainder, None)
            cur = cur.next
            l2 = l2.next
        if carry != 0:
            cur.next = ListNode(carry, None)
        return dummy.next


l1 = ListNode(2, ListNode(4, ListNode(3, None)))
l2 = ListNode(5, ListNode(6, ListNode(4, None)))
printListNode(Solution().addTwoNumbers(l1, l2))
printListNode(Solution().addTwoNumbers(l1, None))
printListNode(Solution().addTwoNumbers(None, l2))
# @lc code=end
