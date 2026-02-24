#include "BinaryTree.h"
class Solution
{
public:
    int findTargetNode(TreeNode *root, int cnt)
    {
        if (root == nullptr)
            return 0;
        vector<int> result;
        inOrder(root, result);
        return result[result.size() - cnt];
    }
    void inOrder(TreeNode *root, vector<int> &result)
    {
        if (root == nullptr)
            return;
        if (root->left)
            inOrder(root->left, result);
        result.push_back(root->val);
        if (root->right)
            inOrder(root->right, result);
    }
};