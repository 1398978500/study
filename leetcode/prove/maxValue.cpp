/*
在一个 m*n 的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值（价值大于
0）。你可以从棋盘的左上角开始拿格子里的礼物，并每次向右或者向下移动一格、直到到达棋盘的右下角。给定一个棋盘及其上面的礼物的价值，请计算你最多能拿到多少价值的礼物？



示例 1:

输入:
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
输出: 12
解释: 路径 1→3→5→2→1 可以拿到最多价值的礼物


提示：

0 < grid.length <= 200
0 < grid[0].length <= 200
*/
class Solution {
public:
    int maxValue(vector<vector<int>>& grid)
    {
        int col = grid.size() - 1;
        int row = grid[0].size() - 1;

        for (int i = 0; i <= col; i++) {
            for (int j = 0; j <= row; j++) {
                // 记录本次 从上一个礼物选过来和 从左边的礼物选过来的价值较大值
                int tmp = 0;
                if (i > 0) {
                    tmp = max(tmp, grid[i - 1][j]);
                }

                if (j > 0) {
                    tmp = max(tmp, grid[i][j - 1]);
                }

                // 记录选到本层 价值最大值
                grid[i][j] += tmp;
            }
        }

        return grid[col][row];
    }
};
