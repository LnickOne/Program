# @lc app=leetcode.cn id=21 lang=python3
# [21] 合并两个有序链表
# https://leetcode.cn/problems/merge-two-sorted-lists/description/
# algorithms
# Easy (68.09%)
# Likes:    3927
# Dislikes: 0
# Total Accepted:    2.3M
# Total Submissions: 3.3M
# Testcase Example:  '[1,2,4]\n[1,3,4]'
# 将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
# 示例 1：
# 输入：l1 = [1,2,4], l2 = [1,3,4]
# 输出：[1,1,2,3,4,4]
# 示例 2：
# 输入：l1 = [], l2 = []
# 输出：[]
# 示例 3：
# 输入：l1 = [], l2 = [0]
# 输出：[0]
# 提示：
# 两个链表的节点数目范围是 [0, 50]
# -100
# l1 和 l2 均按 非递减顺序 排列
# @lc code=start
# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


def printListNode(head):
    temp = head
    while temp:
        print(temp.val, end=" ")
        temp = temp.next
    print()


from typing import Optional


class Solution:
    def mergeTwoLists(
        self, list1: Optional[ListNode], list2: Optional[ListNode]
    ) -> Optional[ListNode]:
        dummy = ListNode(0, None)
        cur = dummy
        while list1 and list2:
            if list1.val <= list2.val:
                cur.next = list1
                list1 = list1.next
                cur = cur.next
            else:
                cur.next = list2
                list2 = list2.next
                cur = cur.next
        if list1:
            cur.next = list1
        elif list2:
            cur.next = list2
        return dummy.next


printListNode(
    Solution().mergeTwoLists(
        ListNode(1, ListNode(2, ListNode(4))), ListNode(1, ListNode(3, ListNode(4)))
    )
)
printListNode(Solution().mergeTwoLists(None, None))
printListNode(Solution().mergeTwoLists(None, ListNode(0)))
printListNode(
    Solution().mergeTwoLists(
        ListNode(1, ListNode(2, ListNode(3))), ListNode(1, ListNode(3, ListNode(4)))
    )
)


# @lc code=end
