/*
输入一个长度为 n 的整数数列，从小到大输出前 m 小的数。

输入格式
第一行包含整数 n 和 m。

第二行包含 n 个整数，表示整数数列。

输出格式
共一行，包含 m 个整数，表示整数数列中前 m 小的数。

数据范围
1≤m≤n≤10^5，
1≤数列中元素≤10^9
输入样例：
5 3
4 5 1 3 2
输出样例：
1 2 3
*/
#include <iostream>

using namespace std;

const int N = 100010;

int h[N];
int sz;

// 下沉操作
void down(int x)
{
    // 存储x与其子节点中的最小
    int t = x;

    int l = x * 2;
    int r = l + 1;

    if (l <= sz && h[l] < h[t]) {
        t = l;
    }

    if (r <= sz && h[r] < h[t]) {
        t = r;
    }

    // 与子节点中的最小值交换并递归
    if (t != x) {
        swap(h[t], h[x]);
        down(t);
    }
}

int main(int argc, char const* argv[])
{
    int n, m;

    cin >> n >> m;

    sz = n;

    // 构造堆
    {
        for (int i = 1; i <= n; i++) { cin >> h[i]; }

        // 从倒数第二层向上 将所有数down一遍
        for (int i = sz / 2; i > 0; i--) { down(i); }
    }

    // 输出最小的三个数
    while (m-- > 0) {
        cout << h[1] << " ";

        // 输出堆顶后将堆顶删除 以便输出下一个
        h[1] = h[sz];
        sz--;
        down(1);
    }

    return 0;
}
