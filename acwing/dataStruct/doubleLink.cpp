/*
实现一个双链表，双链表初始为空，支持 5 种操作：

在最左侧插入一个数；
在最右侧插入一个数；
将第 k 个插入的数删除；
在第 k 个插入的数左侧插入一个数；
在第 k 个插入的数右侧插入一个数
现在要对该链表进行 M 次操作，进行完所有操作后，从左到右输出整个链表。

注意:题目中第 k 个插入的数并不是指当前链表的第 k 个数。例如操作过程中一共插入了 n 个数，则按照插入的时间顺序，这 n 个数依次为：第
1 个插入的数，第 2 个插入的数，…第 n 个插入的数。

输入格式
第一行包含整数 M，表示操作次数。

接下来 M 行，每行包含一个操作命令，操作命令可能为以下几种：

L x，表示在链表的最左端插入数 x。
R x，表示在链表的最右端插入数 x。
D k，表示将第 k 个插入的数删除。
IL k x，表示在第 k 个插入的数左侧插入一个数。
IR k x，表示在第 k 个插入的数右侧插入一个数。
输出格式
共一行，将整个链表从左到右输出。

数据范围
1≤M≤100000
所有操作保证合法。

输入样例：
10
R 7
D 1
L 3
IL 2 10
D 3
IL 2 7
L 8
R 9
IL 4 7
IR 2 2
输出样例：
8 7 7 3 2 9
 */
#include <iostream>

using namespace std;

const int N = 100010;

int e[N];  // 值
int l[N];  // 上一个节点
int r[N];  // 下一个节点
int idx;

void init()
{
    // 0头 1尾节点
    r[0] = 1;
    l[1] = 0;
    idx = 2;
}

void remove(int k)
{
    l[r[k]] = l[k];
    r[l[k]] = r[k];
}

void add_to_right(int k, int x)
{
    e[idx] = x;
    l[idx] = k;
    r[idx] = r[k];
    l[r[k]] = idx;
    r[k] = idx;
    idx++;
}

int main(int argc, char const* argv[])
{
    int m = 0;
    cin >> m;

    init();

    while (m-- > 0) {
        string op;
        int k, x;
        cin >> op;

        if (op == "R") {
            cin >> x;

            // 向最右节点插入表示向尾节点的左边一个节点插入
            add_to_right(l[1], x);
        }
        else if (op == "L") {
            cin >> x;

            // 插入头节点
            add_to_right(0, x);
        }
        else if (op == "D") {
            cin >> k;

            // 移除k+1节点
            remove(k + 1);
        }
        else if (op == "IL") {
            cin >> k >> x;

            add_to_right(l[k + 1], x);
        }
        else if (op == "IR") {
            cin >> k >> x;

            add_to_right(k + 1, x);
        }
    }

    for (int i = r[0]; i != 1; i = r[i]) { cout << e[i] << " "; }
    cout << endl;

    return 0;
}