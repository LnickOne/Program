#include "BinaryTree.h"

class Solution
{
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        return postOrder(root, p, q);
    }
    TreeNode *postOrder(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (root == nullptr)
            return nullptr;
        if (root == p)
            return p;
        if (root == q)
            return q;
        TreeNode *left = postOrder(root->left, p, q);
        TreeNode *right = postOrder(root->right, p, q);
        if (left == nullptr)
            return right;
        if (right == nullptr)
            return left;
        if (left && right)
            return root;
        return root;
    }
};