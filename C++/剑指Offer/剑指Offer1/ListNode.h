// 基础库
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>
// 命名空间
using namespace std;
// 创建链表结构
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
    ~ListNode()
    {
        // 析构函数只释放当前节点，不递归释放整个链表
        // 这样可以避免重复删除和栈溢出问题
        next = nullptr;
    }
};
// 通过数组创建链表
ListNode *createListNode(const vector<int> &arr)

{
    if (arr.size() == 0)
        return nullptr;
    ListNode *head = new ListNode(arr[0]); // 创建头节点
    ListNode *temp = head;                 // 临时指针指向头节点
    for (int i = 1; i < arr.size(); ++i)
    {
        temp->next = new ListNode(arr[i]); // 创建新节点并链接到当前节点后面
        temp = temp->next;                 // 临时指针后移
    }
    return head; // 返回链表头节点
}
// 遍历并打印链表
void printListNode(ListNode *head)
{
    ListNode *temp = head;
    while (temp != nullptr)
    {
        cout << (*temp).val  << " ";
        temp = temp->next;
    }
    cout << endl;
}
// 获得链表的长度并且不影响原来的链表
int GetListLength(ListNode *head)
{
    int length = 0;
    ListNode *cur = head;
    while (cur != nullptr)
    {
        length++;
        cur = cur->next;
    }
    return length;
}
// 克隆链表
ListNode *cloneList(ListNode *head)
{
    if (head == nullptr)
        return nullptr;
    ListNode *new_head = new ListNode(head->val);
    ListNode *cur = new_head;
    while (head->next != nullptr)
    {
        head = head->next;
        cur->next = new ListNode(head->val);
        cur = cur->next;
    }
    return new_head;
}

// 释放整个链表的内存
void deleteList(ListNode *head)
{
    while (head != nullptr)
    {
        ListNode *temp = head;
        head = head->next;
        temp->next = nullptr;
        delete temp;
    }
}