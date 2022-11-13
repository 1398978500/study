/*
在给定的 N 个整数 A1，A2……AN 中选出两个进行 xor（异或）运算，得到的结果最大是多少？

输入格式
第一行输入一个整数 N。

第二行输入 N 个整数 A1～AN。

输出格式
输出一个整数表示答案。

数据范围
1≤N≤10^5,
0≤Ai<2^31
输入样例：
3
1 2 3
输出样例：
3
*/
#include <iostream>

using namespace std;

const int N = 100010;
const int M = 3000000;

int a[N];
int son[M][2];
int idx;

void insert(int x)
{
    int p = 0;
    for (int i = 30; i >= 0; i--) {
        int u = ((x >> i) & (1));

        // 节点不存在
        if (son[p][u] <= 0) {
            son[p][u] = ++idx;
        }

        p = son[p][u];
    }
}

int search(int x)
{
    int res = 0;
    int p = 0;
    for (int i = 30; i >= 0; i--) {
        int u = ((x >> i) & (1));

        // 如果与当前位相反的节点存在则走过去, 并计算返回值
        if (son[p][!u] > 0) {
            res += 1 << i;
            p = son[p][!u];
        }
        else {
            p = son[p][u];
        }
    }

    return res;
}

int main(int argc, char const* argv[])
{
    int n = 0;
    cin >> n;

    int res = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];

        insert(a[i]);
    }

    for (int i = 0; i < n; i++) { res = max(res, search(a[i])); }

    cout << res << endl;

    return 0;
}
