/*
给定一个整数数组，它表示BST(即 二叉搜索树 )的 先序遍历 ，构造树并返回其根。
保证 对于给定的测试用例，总是有可能找到具有给定需求的二叉搜索树。
二叉搜索树 是一棵二叉树，其中每个节点，Node.left 的任何后代的值 严格小于 Node.val ,Node.right 的任何后代的值 严格大于 Node.val。
二叉树的 前序遍历 首先显示节点的值，然后遍历Node.left，最后遍历Node.right。

示例 1：
输入：preorder = [8,5,1,7,10,12]
输出：[8,5,10,1,7,null,12]

示例 2:
输入: preorder = [1,3]
输出: [1,null,3]
*/
#include <iostream>
#include "../BinaryTree.h"
using namespace std;
class Solution
{
public:
    TreeNode *bstFromPreorder(vector<int> &preorder)
    {
        if (preorder.empty())
            return nullptr;
        int root_val = preorder.front();
        TreeNode *root = new TreeNode(root_val);
        if (preorder.size() == 1)
            return root;
        vector<int> left;
        vector<int> right;
        for (int i = 1; i < preorder.size(); i += 1) // 从第二个元素开始遍历，第一个元素是根节点，小于根节点的都在左子树，大于根节点的都在右子树
        {
            if (preorder[i] < root_val)
                left.push_back(preorder[i]);
            else
                right.push_back(preorder[i]);
        }
        root->left = bstFromPreorder(left);
        root->right = bstFromPreorder(right);
        return root;
    }
};
int main()
{
    vector<int> preorder = {8, 5, 1, 7, 10, 12};
    Solution s;
    TreeNode *root = s.bstFromPreorder(preorder);
    printTreeLevelOrder(root);
    printTreeAllTraversals(root);
    delete root;
    return 0;
}