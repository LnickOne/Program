#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    // 构造函数
    // TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
    TreeNode(int value)
    {
        val = value;
        left = nullptr;
        right = nullptr;
    }
    // 析构函数
    ~TreeNode()
    {
        delete left;
        delete right;
    }
};

TreeNode *createBinaryTree(const vector<int> &vec) // 创建二叉树
{
    if (vec.empty())
    {
        return nullptr;
    }
    queue<TreeNode *> nodes;
    TreeNode *root = new TreeNode(vec[0]);
    nodes.push(root);
    int i = 1;
    while (!nodes.empty() && i < vec.size())
    {
        TreeNode *node = nodes.front();
        nodes.pop();
        if (i < vec.size() && vec[i] != -1)
        {
            node->left = new TreeNode(vec[i]);
            nodes.push(node->left);
        }
        i += 1;
        if (i < vec.size() && vec[i] != -1)
        {
            node->right = new TreeNode(vec[i]);
            nodes.push(node->right);
        }
        i += 1;
    }
    return root;
}
