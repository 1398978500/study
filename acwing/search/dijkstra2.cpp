/*
 *850. Dijkstra求最短路 II
 给定一个 n 个点 m 条边的有向图，图中可能存在重边和自环，所有边权均为非负值。

请你求出 1 号点到 n 号点的最短距离，如果无法从 1 号点走到 n 号点，则输出 −1。

输入格式
第一行包含整数 n 和 m。

接下来 m 行每行包含三个整数 x,y,z，表示存在一条从点 x 到点 y 的有向边，边长为 z。

输出格式
输出一个整数，表示 1 号点到 n 号点的最短距离。

如果路径不存在，则输出 −1。

数据范围
1≤n,m≤1.5×10^5,图中涉及边长均不小于 0，且不超过 10000。
数据保证：如果最短路存在，则最短路的长度不超过 10^9。

输入样例：
3 3
1 2 2
2 3 1
1 3 4
输出样例：
3
 * */


#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

using PII = pair<int, int>;

const int N = 150010;
// 稀疏图用邻接表存储 w存储idx这条边的距离
int h[N], e[N], w[N], ne[N], idx;
bool st[N];
// 优先队列，first:源点到存储点的距离 second:点
priority_queue<PII, vector<PII>, greater<PII>> que;
int n, m;
int d[N];

void add(int a, int b, int c)
{
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx++;
}

int dijkstra()
{
    // 初始化距离
    memset(d, 0x3f, sizeof d);
    d[1] = 0;
    que.emplace(0, 1);

    while(!que.empty()){
        auto t = que.top();
        que.pop();

        // 优先队列堆顶元素就是未找过的距离最小的点
        int dis = t.first;
        int point = t.second;

        if(st[point]){
            continue;
        }
        st[point] = true;

        for(int i = h[point]; i != -1; i = ne[i]) {
            int j = e[i];
            if(d[j] > dis + w[i]) {
                d[j] = dis + w[i];
                que.emplace(d[j], j);
            }
        }
    }

    if(d[n] == 0x3f3f3f3f) return -1;

    return d[n];
}

int main()
{
    memset(h, -1, sizeof h);
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }

    cout << dijkstra() << endl;

    return 0;
}
