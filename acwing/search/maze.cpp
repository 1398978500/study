/*
给定一个 n×m 的二维整数数组，用来表示一个迷宫，数组中只包含 0 或 1，其中 0 表示可以走的路，1 表示不可通过的墙壁。

最初，有一个人位于左上角 (1,1) 处，已知该人每次可以向上、下、左、右任意一个方向移动一个位置。

请问，该人从左上角移动至右下角 (n,m) 处，至少需要移动多少次。

数据保证 (1,1) 处和 (n,m) 处的数字为 0，且一定至少存在一条通路。

输入格式
第一行包含两个整数 n 和 m。

接下来 n 行，每行包含 m 个整数（0 或 1），表示完整的二维数组迷宫。

输出格式
输出一个整数，表示从左上角移动至右下角的最少移动次数。

数据范围
1≤n,m≤100
输入样例：
5 5
0 1 0 0 0
0 1 0 1 0
0 0 0 0 0
0 1 1 1 0
0 0 0 1 0
输出样例：
8
*/
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int N = 110;

typedef pair<int, int> PII;

int n, m;
int g[N][N];     // 迷宫
int d[N][N];     // 移动次数 -1表示没走过
queue<PII> que;  // 可走的点

int bfs()
{
    que.emplace(0, 0);

    memset(d, -1, sizeof d);
    d[0][0] = 0;

    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

    while (!que.empty()) {
        auto t = que.front();
        que.pop();

        // 遍历上下左右四个方向是否可以走 若可以则加入到队列并且记录移动次数
        for (int i = 0; i < 4; i++) {
            int x = t.first + dx[i];
            int y = t.second + dy[i];

            // 没有越界并且可以走并且没走过
            if (x >= 0 && x < n && y >= 0 && y < m && g[x][y] == 0 && d[x][y] == -1) {
                d[x][y] = d[t.first][t.second] + 1;
                que.emplace(x, y);
            }
        }
    }

    return d[n - 1][m - 1];
}

int main(int argc, char const* argv[])
{
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) { cin >> g[i][j]; }
    }

    cout << bfs() << endl;

    return 0;
}
