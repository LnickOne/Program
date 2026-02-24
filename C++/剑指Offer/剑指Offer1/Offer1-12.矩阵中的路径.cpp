/* > 题目难度: 中等

> [原题链接](https://leetcode-cn.com/problems/ju-zhen-zhong-de-lu-jing-lcof/)题目描述

请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一格开始，每一步可以在矩阵中向左、右、上、下移动一格。如果一条路径经过了矩阵的某一格，那么该路径不能再次进入该格子。例如，在下面的 3×4 的矩阵中包含一条字符串“bfce”的路径（路径中的字母用加粗标出）。

[["a","b","c","e"],
["s","f","c","s"],
["a","d","e","e"]]

但矩阵中不包含字符串“abfb”的路径，因为字符串的第一个字符 b 占据了矩阵中的第一行第二个格子之后，路径不能再次进入这个格子。

- 1 <= board.length <= 200
- 1 <= board[i].length <= 200题目样例
示例 1

输入

board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"

输出

true
示例 2

输入

board = [["a","b"],["c","d"]], word = "abcd"

输出

false题目思考

1. 有没有什么直观思路?
2. 如何判断某个字符是否已经被访问?解决方案
思路

分析

- 分析题意, 这道题需要求目标字符串的路径, 且只要找到一个满足条件的即可, 所以特别适合用 DFS 来做. 因为 DFS 比较方便记录每条遍历过的路径, 正好可以用在这里
- 所以我们可以从任意一个字符开始, 依次比较它和目标字符串当前下标对应的字符, 如果相等的话, 就可以继续向四周遍历, 同时字符串下标加 1
- 直到字符串下标达到字符串长度, 这个时候就说明我们找到了一个满足要求的路径, 直接返回 true 即可
- 而如果遍历过程中某个字符并不匹配, 我们就不要继续往下遍历下去了, 因为肯定不满足条件
- 另外注意需要判断某个字符是否已经访问过, 所以我们需要额外定义一个 visit 集合,
- 用于存储已经访问的元素行列下标: 在递归调用某个字符之前将其加入行列下标加入集合中, 调用结束后还要将其移除, 恢复现场, 避免这个下标之后在其他路径中不能被用到

实现
- 经典的 DFS, 需要额外 visit 集合, 以及当前目标字符串的下标
- 依次遍历矩阵的每个字符, 如果当前字符与目标字符串的开头相同, 就以它为起点进行 DFS, 如果发现一条满足条件的路径就直接返回 true, 否则继续遍历
- **优化**
  - visit 集合可以利用对原始矩阵的字符替换为 None 或其他不存在的字符代替, 而恢复时再将其替换回来即可, 这样可以节省一些空间
  - 如果某个方向已经找到路径了, 就没必要继续遍历下去, 直接返回即可, 这样剪枝可以节省一些时间
- 下面代码对各个步骤都有详细解释, 特别是时间和空间优化的部分, 方便大家理解
复杂度

- 时间复杂度 `O((3^L)*RC)`
  - 假设 L 是目标字符串长度, RC 是矩阵行和列数
  - 每次递归调用都需要考虑 3 个方向(不可能返回上一个字符, 因为它已经被访问了, 不会重复被访问, 所以是 3 个方向), 最多要调用到长度为 L 的路径, 这部分就是 `O(3^L)`
  - 而一共需要遍历 RC 个字符, 这部分是`O(RC)`
  - 所以时间复杂度是`O((3^L)*RC)`
- 空间复杂度 `O(L)`
  - 优化掉 visit 集合后, 只需要考虑递归的栈的空间, 而递归深度最大为 L(当路径长度超过 L 后没必要继续下去), 所以空间复杂度就是`O(L)`
 */
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
  bool exist(vector<vector<char>> &board, string word)
  {
    // 从任意一个字符开始, 依次比较它和目标字符串当前下标对应的字符, 如果相等的话, 就可以继续向四周遍历, 同时字符串下标加 1
    // 直到字符串下标达到字符串长度, 这个时候就说明我们找到了一个满足要求的路径, 直接返回 true 即可
    // 而如果遍历过程中某个字符并不匹配, 我们就不要继续往下遍历下去了, 因为肯定不满足条件
    // 另外注意需要判断某个字符是否已经访问过, 所以我们需要额外定义一个 visit 集合, 用于存储已经访问的元素行列下标
    // 在递归调用某个字符之前将其加入行列下标加入集合中, 调用结束后还要将其移除, 恢复现场, 避免这个下标之后在其他路径中不能被用到
    int rows = board.size();
    int cols = board[0].size();
    for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; ++j)
      {
        if (board[i][j] == word[0])
        {
          if (dfs(board, word, i, j, 0))
          {
            return true;
          }
        }
      }
    }
    return false;
  }

private:
  bool dfs(vector<vector<char>> &board, string &word, int row, int col, int index)
  {
    // 下标越界或者当前字符不匹配, 直接返回false
    if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size() || board[row][col] != word[index])
    {
      return false;
    }
    // 字符串下标达到字符串长度, 说明找到了一个满足条件的路径, 直接返回 true
    if (index == word.size() - 1)
    {
      return true;
    }
    // 标记当前字符已经访问过
    board[row][col] = '\0';
    // 向四周遍历
    bool res = dfs(board, word, row + 1, col, index + 1) || dfs(board, word, row - 1, col, index + 1) || dfs(board, word, row, col + 1, index + 1) || dfs(board, word, row, col - 1, index + 1);
    // 恢复现场
    board[row][col] = word[index];
    return res;
  }
};

int main()
{
  Solution s;
  vector<vector<char>> board = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
  string word = "ABCCED";
  cout << s.exist(board, word) << endl;
  return 0;
}
