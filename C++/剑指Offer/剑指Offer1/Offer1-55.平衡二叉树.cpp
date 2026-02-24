#include "BinaryTree.h"
class Solution
{
public:
    bool isBalanced(TreeNode *root)
    {
        if (root == nullptr)
            return true;
        return depth(root) == -1 ? false : true;
    }
    int depth(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        int left = depth(root->left);
        int right = depth(root->right);
        int diff_depth = abs(left - right);
        if (left == -1)
            return -1;
        if (right == -1)
            return -1;
        if (diff_depth > 1)
            return -1;
        return max(left, right) + 1;
    }
};
int main()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    Solution s;
    bool isBalanced = s.isBalanced(root);
    cout << isBalanced << endl;
    delete root;
    return 0;
}