/*
给定一颗树，树中包含 n
 个结点（编号 1∼n
）和 n−1
 条无向边。

请你找到树的重心，并输出将重心删除后，剩余各个连通块中点数的最大值。

重心定义：重心是指树中的一个结点，如果将这个点删除后，剩余各个连通块中点数的最大值最小，那么这个节点被称为树的重心。

输入格式
第一行包含整数 n
，表示树的结点数。

接下来 n−1
 行，每行包含两个整数 a
 和 b
，表示点 a
 和点 b
 之间存在一条边。

输出格式
输出一个整数 m
，表示将重心删除后，剩余各个连通块中点数的最大值。

数据范围
1≤n≤105
输入样例
9
1 2
1 7
1 4
2 8
2 5
4 3
3 9
4 6
输出样例：
4
*/

#include <iostream>
#include <cstring>

using namespace std;


const int N = 1e5 + 10; // 数据范围是10的5次方
const int M = 2 * N; // 以有向图的格式存储无向图，所以每个节点至多对应2n-2条边

int h[N]; // 邻接表存储树，有n个节点，所以需要n个队列头节点
int e[M]; // 存储元素
int ne[M]; // 存储列表的next值
int idx; // 单链表指针
int n; // 题目所给的输入，n个节点
int ans = N; // 表示重心的所有的子树中，最大的子树的结点数目

bool st[N]; // 记录节点是否被访问过，访问过则标记为true

// a对应的单链表中插入b a是根
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

// 返回当前节点的父节点被删除后总节点数
int dfs(int u) {
    //
    int res = 0;
    st[u] = true;
    int sum = 1;

    for(int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if(!st[j]) {
            int s = dfs(j);
            res = max(s, res);
            sum += s;
        }
    }

    res = max(res, n - sum);
    ans = min(ans, res);

    return sum;
}

int main(int argc, char *argv[]) {
    memset(h, -1, sizeof h);
    cin >> n;

    // n个节点 n-1条边
    for(int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }

    // 从哪个节点开始,都能遍历所有
    dfs(1);

    cout << ans << endl;
    return 0;
}


