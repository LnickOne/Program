/*
给定两个整数数组 preorder 和 inorder ，
其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。
示例 1:
输入: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
输出: [3,9,20,null,null,15,7]
示例 2:
输入: preorder = [-1], inorder = [-1]
输出: [-1]
 */
#include "../BinaryTree.h"
class Solution
{
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        if (preorder.empty() || inorder.empty())
            return nullptr;
        int root_val = preorder.front();
        TreeNode *root = new TreeNode(root_val);
        int root_index;
        for (int i = 0; i < inorder.size(); i += 1)
        {
            if (inorder[i] == root_val)
            {
                root_index = i;
                break;
            }
        }
        // 使用构造函数直接初始化子数组
        vector<int> inorder_left(inorder.begin(), inorder.begin() + root_index);
        vector<int> inorder_right(inorder.begin() + root_index + 1, inorder.end());
        vector<int> preorder_left(preorder.begin() + 1, preorder.begin() + 1 + inorder_left.size());
        vector<int> preorder_right(preorder.begin() + 1 + inorder_left.size(), preorder.end());
        root->left = buildTree(preorder_left, inorder_left);
        root->right = buildTree(preorder_right, inorder_right);
        return root;
    }
};

int main()
{
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};
    Solution solution;
    TreeNode *root = solution.buildTree(preorder, inorder);
    delete root;
    return 0;
}