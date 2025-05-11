/*
849. Dijkstra求最短路 I
给定一个 n
 个点 m
 条边的有向图，图中可能存在重边和自环，所有边权均为正值。

请你求出 1
 号点到 n
 号点的最短距离，如果无法从 1
 号点走到 n
 号点，则输出 −1
。

输入格式
第一行包含整数 n
 和 m
。

接下来 m
 行每行包含三个整数 x,y,z
，表示存在一条从点 x
 到点 y
 的有向边，边长为 z
。

输出格式
输出一个整数，表示 1
 号点到 n
 号点的最短距离。

如果路径不存在，则输出 −1
。

数据范围
1≤n≤500
,
1≤m≤105
,
图中涉及边长均不超过10000。

输入样例：
3 3
1 2 2
2 3 1
1 3 4
输出样例：
3
*/
#include <iostream>
#include <cstring>

using namespace std;

const int N = 510;
int g[N][N];
int d[N];
bool st[N];
int n, m;

int dijkstra() {
    memset(d, 0x3f, sizeof d);
    d[1] = 0;

    for(int i = 0; i < n; i ++) {
        int t = -1;
        for(int j = 1; j <= n; j++) {
            if(!st[j] && (t == -1 || d[t] > d[j])) {
                t = j;  
            }
        }

        st[t] = true;

        for(int j = 1; j <= n; j++) {
            d[j] = min(d[j], d[t] + g[t][j]);
        }
    }

    if(d[n] == 0x3f3f3f3f) return -1;
    return d[n];
}

int main () {
    cin >> n >> m;
    memset(g, 0x3f, sizeof g);
    
    for(int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        g[x][y] = min(g[x][y], z);
    }

    cout << dijkstra() << endl;

    return 0;
}
