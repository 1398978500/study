/*
给定一个 n
 个点 m
 条边的有向图，点的编号是 1
 到 n
，图中可能存在重边和自环。

请输出任意一个该有向图的拓扑序列，如果拓扑序列不存在，则输出 −1
。

若一个由图中所有点构成的序列 A
 满足：对于图中的每条边 (x,y)
，x
 在 A
 中都出现在 y
 之前，则称 A
 是该图的一个拓扑序列。

输入格式
第一行包含两个整数 n
 和 m
。

接下来 m
 行，每行包含两个整数 x
 和 y
，表示存在一条从点 x
 到点 y
 的有向边 (x,y)
。

输出格式
共一行，如果存在拓扑序列，则输出任意一个合法的拓扑序列即可。

否则输出 −1
。

数据范围
1≤n,m≤105
输入样例：
3 3
1 2
2 3
1 3
输出样例：
1 2 3

*/

#include <iostream>
#include <cstring>

using namespace std;

const int N = 100010;

int n, m;
// 邻接表
int h[N], e[N], ne[N], idx;
// 队列
int q[N], hh, tt;
// 存入度
int d[N];

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void toplogicalSort() {
    // 将所有入度为0的点入队
    for(int i = 1; i <= n; i++) {
        if(d[i] <= 0) {
            q[++tt] = i;
        }
    }

    // 队列不空
    while(hh <= tt) {
        int t = q[hh++];
        // 遍历队头能到达的所有点
        for(int i = h[t]; i != -1; i = ne[i]) {
            // 假如删掉队头 能到达的节点入度-1
            int b = e[i];
            d[b] --;
            if(d[b] <= 0) {
                q[++tt] = b;
            }
        }
    }

    if(tt + 1 < n) {
        cout << -1 << endl;
        return;
    }

    // 当前q中存储的点即为一个拓扑序列
    for(int i = 0; i < n; i++) {
        cout << q[i] << " ";
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    tt = -1;
    memset(h, -1, sizeof(h));
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        d[b]++;
    }

    toplogicalSort();

    return 0;
}

