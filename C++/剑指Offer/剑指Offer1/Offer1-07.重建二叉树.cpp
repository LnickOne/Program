/*
题目描述
输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
输入
前序遍历 preorder = [3,9,20,15,7]
中序遍历 inorder = [9,3,15,20,7]
输出
    3
   / \
  9  20
    /  \
   15   7
题目思考
如果利用前序和中序遍历的性质?
假如题目变为中序和后序遍历能否重建出唯一的二叉树? 前序和后序呢?
假如题目中节点值有重复的, 还能重建出唯一的二叉树吗? 为什么?
解决方案
方案 1
回忆前序和中序遍历的性质: 前序是根=>左子树部分=>右子树部分, 中序是左子树部分=>根=>右子树部分
所以对于同一个树的前序和中序遍历, 其前序遍历的第一个元素一定是根, 而这个根在中序遍历中就是左子树和右子树的分界点
实现
根据上面分析, 一个直观思路就是我们将子树部分看做一个整体, 递归调用得出左右子树的根节点, 然后将当前根节点的左右儿子指向它们即可, 这就是典型的分治思想, 将大问题分解为小问题进行解决
先设计递归参数, 这里需要传入前序和中序遍历当前的起点和终点, 用于确定当前的树的部分, 初始传入自然就是整个前序和中序数组的起点和终点了.
然后定义递归出口, 如果起点大于终点, 就说明这个子树不存在(比如当前节点缺少左子树等), 返回空; 如果起点恰好等于终点, 则表示当前子树节点数目只有 1, 就是根节点, 直接返回该节点即可
参数和出口都确定了, 接下来就是通常情况下的处理(即当前子树节点数目多于 1 个)
根据前序起点, 确定根的值
找到该根在中序遍历中的位置 im (唯一, 因为每个节点值都不同)
以 im 为分界点, 将中序划分为左子树和右子树部分
对于前序而言, 其左右子树的节点数目和中序的左右子树节点数目相同, 利用这一点就能确定前序的左右子树区间的起点和终点
递归传入左右子树各自的前序和中序区间, 得到左右子树根节点
将当前根节点的左右儿子指向它们, 返回当前根节点
优化: 在第 3.2 步中, 如果我们每次都从头开始遍历中序数组, 找根的值对应的中序下标的话, 效率太低. 注意到每个节点值都不同, 所以我们完全可以定义一个节点值到中序下标的字典, 预处理得到映射关系, 这样只需要一次查表就能得到中序下标位置, 大大降低了时间复杂度
复杂度
时间复杂度 O(N)
前序和中序数组的每个元素只需要访问一遍
空间复杂度 O(N)
字典以及递归栈的消耗
*/
#include <vector>
#include <iostream>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution
{
public:
    TreeNode *deduceTree(vector<int> &preorder, vector<int> &inorder)
    {
        if (preorder.empty() || inorder.empty())
        {
            return nullptr;
        }
        TreeNode *root = new TreeNode(preorder.front());
        int root_index;
        for (int i = 0; i < inorder.size(); i++)
        {
            if (inorder[i] == preorder.front())
            {
                root_index = i;
                break;
            }
        }
        vector<int> preorder_left = vector<int>(preorder.begin() + 1, preorder.begin() + 1 + root_index);
        vector<int> preorder_right = vector<int>(preorder.begin() + 1 + root_index, preorder.end());
        vector<int> inorder_left = vector<int>(inorder.begin(), inorder.begin() + root_index);
        vector<int> inorder_right = vector<int>(inorder.begin() + root_index + 1, inorder.end());
        root->left = deduceTree(preorder_left, inorder_left);
        root->right = deduceTree(preorder_right, inorder_right);
        return root;
    }
};
int main()
{
    Solution s;
    vector<int> preorder{3, 9, 20, 15, 7};
    vector<int> inorder{9, 3, 15, 20, 7};
    TreeNode *root = s.deduceTree(preorder, inorder);
    cout << root->val << " ";
    cout << root->left->val << " ";
    cout << root->right->val << " ";
    cout << root->right->left->val << " ";
    cout << root->right->right->val << " " << endl;
    delete root;
    return 0;
}