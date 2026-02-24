#include "BinaryTree.h"
class Solution
{
public:
    int calculateDepth(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        int left = calculateDepth(root->left);
        int right = calculateDepth(root->right);
        int depth = max(left, right) + 1;
        return depth;
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
    int depth = s.calculateDepth(root);
    cout << depth << endl;
    delete root;
    return 0;
}