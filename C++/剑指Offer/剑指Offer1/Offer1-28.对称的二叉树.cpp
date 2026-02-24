#include "BinaryTree.h"
class Solution
{
public:
    bool checkSymmetricTree(TreeNode *root)
    {
        if (root == nullptr)
            return true;
        return compare(root->left, root->right);
    }
    bool compare(TreeNode *left, TreeNode *right)
    {
        if (left == nullptr && right == nullptr)
            return true;
        if (left == nullptr && right != nullptr)
            return false;
        if (left != nullptr && right == nullptr)
            return false;
        if (left->val != right->val)
            return false;
        bool left_result = compare(left->right, right->left);
        bool right_result = compare(left->left, right->right);
        return left_result && right_result;
    }
};
int main()
{
    TreeNode *root = createBinaryTree({1, 2, 2, 3, 4, 4, 3});
    Solution s;
    bool result = s.checkSymmetricTree(root);
    cout<<result<<endl;
    return 0;
}