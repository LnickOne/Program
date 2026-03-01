#include <iostream>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;
struct TreeNode // 树结构体
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    ~TreeNode()
    {
        delete left;
        delete right;
        left = nullptr;
        right = nullptr;
    }
};

TreeNode *createBinaryTree(const std::vector<int> &arr) // 创建二叉树
{
    if (arr.empty())
        return nullptr;
    std::queue<TreeNode *> queue;
    TreeNode *root = new TreeNode(arr[0]);
    queue.push(root);
    int i = 1;
    while (!queue.empty() && i < arr.size())
    {
        TreeNode *node = queue.front();
        queue.pop();
        if (i < arr.size() && arr[i] != -1)
        {
            node->left = new TreeNode(arr[i]);
            queue.push(node->left);
        }
        i++;
        if (i < arr.size() && arr[i] != -1)
        {
            node->right = new TreeNode(arr[i]);
            queue.push(node->right);
        }
        i++;
    }
    return root;
}

// ==================== 打印二叉树函数 ====================

// 1. 层序遍历打印（按层打印，用-1表示null）
void printTreeLevelOrder(TreeNode *root)
{
    if (!root)
    {
        cout << "[]" << endl;
        return;
    }
    
    queue<TreeNode *> q;
    q.push(root);
    vector<int> result;
    
    while (!q.empty())
    {
        TreeNode *node = q.front();
        q.pop();
        
        if (node)
        {
            result.push_back(node->val);
            q.push(node->left);
            q.push(node->right);
        }
        else
        {
            result.push_back(-1);  // 用-1表示null
        }
    }
    
    // 去除末尾多余的-1
    while (!result.empty() && result.back() == -1)
    {
        result.pop_back();
    }
    
    // 打印结果
    cout << "[";
    for (int i = 0; i < result.size(); i++)
    {
        if (result[i] == -1)
            cout << "null";
        else
            cout << result[i];
        
        if (i < result.size() - 1)
            cout << ", ";
    }
    cout << "]" << endl;
}

// 2. 树形结构打印（可视化树形）
void printTreeVisual(TreeNode *root, int space = 0, int level = 0)
{
    if (!root)
        return;
    
    const int INDENT = 4;  // 每层缩进空格数
    space += INDENT;
    
    // 先打印右子树
    printTreeVisual(root->right, space, level + 1);
    
    // 打印当前节点
    cout << endl;
    for (int i = INDENT; i < space; i++)
        cout << " ";
    cout << root->val << endl;
    
    // 打印左子树
    printTreeVisual(root->left, space, level + 1);
}

// 辅助函数：打印树形结构的包装函数
void printTree(TreeNode *root)
{
    if (!root)
    {
        cout << "空树" << endl;
        return;
    }
    cout << "树形结构打印：" << endl;
    printTreeVisual(root);
    cout << endl;
}

// 3. 前序遍历打印
void printTreePreOrder(TreeNode *root)
{
    if (!root)
        return;
    cout << root->val << " ";
    printTreePreOrder(root->left);
    printTreePreOrder(root->right);
}

// 4. 中序遍历打印
void printTreeInOrder(TreeNode *root)
{
    if (!root)
        return;
    printTreeInOrder(root->left);
    cout << root->val << " ";
    printTreeInOrder(root->right);
}

// 5. 后序遍历打印
void printTreePostOrder(TreeNode *root)
{
    if (!root)
        return;
    printTreePostOrder(root->left);
    printTreePostOrder(root->right);
    cout << root->val << " ";
}

// 6. 打印所有遍历方式
void printTreeAllTraversals(TreeNode *root)
{
    if (!root)
    {
        cout << "空树" << endl;
        return;
    }
    
    cout << "前序遍历: ";
    printTreePreOrder(root);
    cout << endl;
    
    cout << "中序遍历: ";
    printTreeInOrder(root);
    cout << endl;
    
    cout << "后序遍历: ";
    printTreePostOrder(root);
    cout << endl;
    
    cout << "层序遍历: ";
    printTreeLevelOrder(root);
}

