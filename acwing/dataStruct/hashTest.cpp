/*
维护一个集合，支持如下几种操作：

I x，插入一个数 x；
Q x，询问数 x 是否在集合中出现过；
现在要进行 N 次操作，对于每个询问操作输出对应的结果。

输入格式
第一行包含整数 N，表示操作数量。

接下来 N 行，每行包含一个操作指令，操作指令为 I x，Q x 中的一种。

输出格式
对于每个询问指令 Q x，输出一个询问结果，如果 x 在集合中出现过，则输出 Yes，否则输出 No。

每个结果占一行。

数据范围
1≤N≤10^5
−10^9≤x≤10^9
输入样例：
5
I 1
I 2
I 3
Q 2
Q 5
输出样例：
Yes
No
*/

#include <cstring>
#include <iostream>

using namespace std;

const int N = 100003;  // 大于100000的质数

int h[N];   // 存储当前节点储存位置的链表头
int e[N];   // 节点值
int ne[N];  // 下一个
int idx;    // 第几个点

void insert(int x)
{
    int t = ((x % N) + N) % N;

    e[idx] = x;
    ne[idx] = h[t];
    h[t] = idx++;
}

bool find(int x)
{
    int t = ((x % N) + N) % N;

    for (int i = h[t]; i != -1; i = ne[i]) {
        if (e[i] == x) {
            return true;
        }
    }

    return false;
}

int main(int argc, char const* argv[])
{
    int n = 0;
    cin >> n;

    memset(h, -1, sizeof h);

    while (n-- > 0) {
        char op[2];
        int x = 0;
        cin >> op >> x;

        if (op[0] == 'I') {
            insert(x);
        }
        else if (op[0] == 'Q') {
            if (find(x)) {
                cout << "Yes" << endl;
            }
            else {
                cout << "No" << endl;
            }
        }
    }

    return 0;
}
