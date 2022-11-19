/*
动物王国中有三类动物 A,B,C，这三类动物的食物链构成了有趣的环形。

A 吃 B，B 吃 C，C 吃 A。

现有 N 个动物，以 1∼N 编号。

每个动物都是 A,B,C 中的一种，但是我们并不知道它到底是哪一种。

有人用两种说法对这 N 个动物所构成的食物链关系进行描述：

第一种说法是 1 X Y，表示 X 和 Y 是同类。

第二种说法是 2 X Y，表示 X 吃 Y。

此人对 N 个动物，用上述两种说法，一句接一句地说出 K 句话，这 K 句话有的是真的，有的是假的。

当一句话满足下列三条之一时，这句话就是假话，否则就是真话。

当前的话与前面的某些真的话冲突，就是假话；
当前的话中 X 或 Y 比 N 大，就是假话；
当前的话表示 X 吃 X，就是假话。
你的任务是根据给定的 N 和 K 句话，输出假话的总数。

输入格式
第一行是两个整数 N 和 K，以一个空格分隔。

以下 K 行每行是三个正整数 D，X，Y，两数之间用一个空格隔开，其中 D 表示说法的种类。

若 D=1，则表示 X 和 Y 是同类。

若 D=2，则表示 X 吃 Y。

输出格式
只有一个整数，表示假话的数目。

数据范围
1≤N≤50000,
0≤K≤100000
输入样例：
100 7
1 101 1
2 1 2
2 2 3
2 3 3
1 1 3
2 3 1
1 5 5
输出样例：
3
*/

#include <iostream>

using namespace std;

const int N = 50010;

int p[N];  // 父节点
int d[N];  // 节点到父节点的距离 %3的值  0被1吃  1被2吃  2被0吃

int findParent(int x)
{
    if (x != p[x]) {
        int t = findParent(p[x]);
        d[x] += d[p[x]];
        p[x] = t;
    }

    return p[x];
}

int main(int argc, char* argv[])
{
    int m, n;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) { p[i] = i; }

    int res = 0;
    while (m-- > 0) {
        int op, x, y;

        cin >> op >> x >> y;

        // 题意 x或y不符合要求则为假
        if (x > n || y > n) {
            res++;
            continue;
        }

        int px = findParent(x);
        int py = findParent(y);

        // x与y同类
        if (1 == op) {
            // 祖宗节点相同 但不是同一类则为假
            if (px == py && ((d[x] - d[y]) % 3) != 0) {
                res++;
            }
            // 祖宗节点不同 则将其合并
            else if(px != py){
                p[px] = py;
                d[px] = d[y] - d[x];
            }
        }
        // x吃y
        else {
            if (px == py && (d[x] - d[y] - 1) % 3 != 0) {
                res++;
            }
            else if(px != py) {
                p[px] = py;
                d[px] = d[y] + 1 - d[x];
            }
        }
    }

    cout << res << endl;

    return 0;
}
