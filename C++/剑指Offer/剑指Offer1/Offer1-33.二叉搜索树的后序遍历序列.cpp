#include "BinaryTree.h"
class Solution
{
public:
    bool verifyTreeOrder(vector<int> &postorder)
    {
        if (postorder.empty())
            return true;
        return isVaild(0, postorder.size() - 1, postorder);
    }

    bool isVaild(int left, int right, vector<int> &postorder)
    {
        /*
        终止条件： 当 left≥right，说明此子树节点数量 ≤1 ，无需判别正确性，因此直接返回 true ；
        递推工作：
        划分左右子树： 遍历后序遍历的 [left,right] 区间元素，寻找 第一个大于根节点 的节点，索引记为 mid 。
        此时，可划分出左子树区间 [left,mid−1] 、右子树区间 [mid,right−1] 、根节点索引 right 。
        判断是否为二叉搜索树：
        左子树区间 [i,m−1] 内的所有节点都应 < postorder[j] 。
        而第 1.划分左右子树 步骤已经保证左子树区间的正确性，因此只需要判断右子树区间即可。
        右子树区间 [m,j−1] 内的所有节点都应 > postorder[j] 。
        实现方式为遍历，当遇到 ≤postorder[right] 的节点则跳出；则可通过 p=right 判断是否为二叉搜索树。
        */
        if (left >= right)
        {
            return true;
        }
        int i = left;
        while (postorder[i] < postorder[right])
            i++;
        int mid = i;
        while (postorder[i] > postorder[right])
            i++;
        if (i < right)
            return false;
        return isVaild(left, mid - 1, postorder) && isVaild(mid, right - 1, postorder);
    }
};

int main()
{
    Solution s;
    vector<int> postorder = {4, 8, 6, 12, 16, 14, 10};
    bool result = s.verifyTreeOrder(postorder);
    cout << result << endl;
    return 0;
}