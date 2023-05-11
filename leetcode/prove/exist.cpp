/*
给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。



例如，在下面的 3×4 的矩阵中包含单词 "ABCCED"（单词中的字母已标出）。





示例 1：

输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
输出：true
示例 2：

输入：board = [["a","b"],["c","d"]], word = "abcd"
输出：false


提示：

m == board.length
n = board[i].length
1 <= m, n <= 6
1 <= word.length <= 15
board 和 word 仅由大小写英文字母组成
*/

class Solution {
public:
    bool isValid(vector<vector<char>>& board, string word, int level, int x, int y, vector<vector<bool>>& bRec)
    {
        // 不符合
        if (board[x][y] != word[level]) {
            return false;
        }
        // 已经找到了
        else if ((size_t)level >= word.length() - 1) {
            return true;
        }

        int row = board.size();
        int col = board[0].size();

        int x1[4] = {-1, 0, 1, 0}, y1[4] = {0, 1, 0, -1};

        bool res = false;

        // 标记
        bRec[x][y] = true;
        // 遍历上下左右四个点
        for (int i = 0; i < 4; i++) {
            int newx = x + x1[i], newy = y + y1[i];

            // 看哪个没走过的点符合要求
            if (newx >= 0 && newx < row && newy >= 0 && newy < col && !bRec[newx][newy]) {
                if (isValid(board, word, level + 1, newx, newy, bRec)) {
                    res = true;
                    break;
                }
            }
        }
        bRec[x][y] = false;

        return res;
    }

    bool exist(vector<vector<char>>& board, string word)
    {
        int row = board.size();
        int col = board[0].size();
        vector<vector<bool>> bRec(row, vector<bool>(col));  // 记录是否走过

        // 每个点都可做起点
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (isValid(board, word, 0, i, j, bRec)) {
                    return true;
                }
            }
        }

        return false;
    }
};
