/*
> 题目难度 : 中等
> [原题链接](https : leetcode - cn.com / problems / shu - de - zi - jie - gou - lcof /)
 ##题目描述
输入两棵二叉树 A 和 B，判断 B 是不是 A 的子结构。(约定空树不是任意一个树的子结构)
B 是 A 的子结构， 即 A 中有出现和 B 相同的结构和节点值。
例如 : 给定的树 A :
 ``` 3
     / \
    4   5
   / \
  1   2
 ```
    给定的树 B：

 ``` 4 
   /
  1
 ```
    返回 true，因为 B 与 A 的一个子树拥有相同的结构和节点值。
    0 <=
    节点个数 <= 10000
    ##题目样例
    ## #示例 1
    ####输入
        A = [ 1, 2, 3 ],
        B = [ 3, 1 ]
        ####输出
        false
        ## #示例 2
        ####输入
        A = [ 3, 4, 5, 1, 2 ],
        B = [ 4, 1 ]
        ####输出
        true
        ##题目思考
        1. 子结构有哪些性质
        ?
        ##解决方案
            ## #思路
            - 分析题目,
B 是 A 的子结构的话, 那么 B 的节点结构需要完全是 A 的某一部分, 而且该部分中的一部分子树可以不在 B 中(例如题目中 A 的 2 号节点就不在 B 中) -
所以我们可以额外定义一个方法, 来递归比较当前 A 和 B 节点是否满足子结构关系 - 然后从 A 和 B 的根节点开始调用该方法,
如果当前满足条件就直接返回 true, 否则就将 A 移动到其左右子节点位置, 重新与 B 的根节点比较即可
最差情况是对于每个 A 节点, 都要调用一次 match 方法遍历整个 B 树,
所以时间复杂度是 `O(MN)` - 空间复杂度 `O(M)` -
isSubStructure 递归调用则最多使用 `O(M)` 递归栈空间, match 递归调用使用 `O(min(M, N))`
递归栈空间, 所以整体空间复杂度为 `O(M)`
*/

#include <iostream>
#include <vector>
#include <algorithm>
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
    bool isSubStructure(TreeNode *A, TreeNode *B)
    {
        if (A == nullptr || B == nullptr)
            return false;
        bool mid = Judge(A, B);
        bool left = isSubStructure(A->left, B);
        bool right = isSubStructure(A->right, B);
        return mid || left || right;
    }

    bool Judge(TreeNode *A, TreeNode *B)
    {
        if (A == nullptr)
            return false;
        if (B == nullptr)
            return true;
        bool left = Judge(A->left, B->left);
        bool right = Judge(A->right, B->right);
        return A->val == B->val && left && right;
    }
};

int main()
{
    Solution s;
    TreeNode *A = new TreeNode(1);
    TreeNode *B = new TreeNode(2);
    cout << s.isSubStructure(A, B) << endl;
    return 0;
}
