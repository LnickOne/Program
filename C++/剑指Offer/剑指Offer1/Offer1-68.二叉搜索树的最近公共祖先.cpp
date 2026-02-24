#include "BinaryTree.h"
class Solution
{
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (root == nullptr)
            return nullptr;
        if (root->val > p->val && root->val > q->val)
        {
            TreeNode *left = lowestCommonAncestor(root->left, p, q);
            if (left != nullptr)
                return left;
        }
        if (root->val < p->val && root->val < q->val)
        {
            TreeNode *right = lowestCommonAncestor(root->right, p, q);
            if (right != nullptr)
                return right;
        }
        return root;
    }
};