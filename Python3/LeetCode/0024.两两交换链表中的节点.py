# @lc app=leetcode.cn id=24 lang=python3
# [24] 两两交换链表中的节点
# https://leetcode.cn/problems/swap-nodes-in-pairs/description/
# algorithms
# Medium (74.88%)
# Likes:    2522
# Dislikes: 0
# Total Accepted:    1.3M
# Total Submissions: 1.7M
# Testcase Example:  '[1,2,3,4]'
# 给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。
# 示例 1：
# 输入：head = [1,2,3,4]
# 输出：[2,1,4,3]
# 示例 2：
# 输入：head = []
# 输出：[]
# 示例 3：
# 输入：head = [1]
# 输出：[1]
# 提示：
# 链表中节点的数目在范围 [0, 100] 内
# 0 <= Node.val <= 100
# @lc code=start
# Definition for singly-linked list.
from typing import Optional


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


class Solution:
    def swapPairs(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if not head:
            return head
        dummy = ListNode(0, None)
        cur = dummy
        dummy.next = head
        while cur.next and cur.next.next:
            node_1 = cur.next
            node_3 = cur.next.next.next
            cur.next = cur.next.next  # 0->2 (0指向2)
            cur.next.next = node_1  # 2=1 (2换到1的位置)
            node_1.next = node_3  # 1->3 (1指向3)
            cur = cur.next.next  # 0=2 (0换到2的位置)
        return dummy.next


printListNode(Solution().swapPairs(ListNode(1, ListNode(2, ListNode(3, ListNode(4))))))
printListNode(
    Solution().swapPairs(
        ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))))
    )
)
# @lc code=end
