#include <iostream>
#include "BinaryTree.h"
#include <algorithm>
#include <numeric>

class Solution
{
public:
    vector<vector<int>> pathTarget(TreeNode *root, int target)
    {
        if (root == nullptr)
            return {};
        vector<vector<int>> result;
        vector<int> path;
        backtracking(root, target, path, result);
        return result;
    }
    void backtracking(TreeNode *root, int target, vector<int> &path, vector<vector<int>> &result)
    {
        path.push_back(root->val);
        if (root->left == nullptr && root->right == nullptr) // 抵达叶子节点就是左右子树都为空
        {
            int sum = accumulate(path.begin(), path.end(), 0);
            if (sum == target)
            {
                result.push_back(path);
                return;
            }
        }
        if (root->left)
        {
            backtracking(root->left, target, path, result);
            path.pop_back();
        }
        if (root->right)
        {
            backtracking(root->right, target, path, result);
            path.pop_back();
        }
    }
};
int main()
{
    Solution s;
    TreeNode *root = createBinaryTree({10, 5, 12, 4, 7});
    TreeNode *root1 = createBinaryTree({1, 2});
    vector<vector<int>> result = s.pathTarget(root, 22);
    vector<vector<int>> result1 = s.pathTarget(root1, 1);
    for (auto &path : result)
    {
        for (auto &num : path)
        {
            cout << num << " ";
        }
        cout << endl;
    }
    return 0;
}