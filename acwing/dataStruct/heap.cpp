/*
维护一个集合，初始时集合为空，支持如下几种操作：

I x，插入一个数 x；
PM，输出当前集合中的最小值；
DM，删除当前集合中的最小值（数据保证此时的最小值唯一）；
D k，删除第 k 个插入的数；
C k x，修改第 k 个插入的数，将其变为 x；
现在要进行 N 次操作，对于所有第 2 个操作，输出当前集合的最小值。

输入格式
第一行包含整数 N。

接下来 N 行，每行包含一个操作指令，操作指令为 I x，PM，DM，D k 或 C k x 中的一种。

输出格式
对于每个输出指令 PM，输出一个结果，表示当前集合中的最小值。

每个结果占一行。

数据范围
1≤N≤10^5
−109≤x≤10^9
数据保证合法。

输入样例：
8
I -10
PM
I -10
D 1
C 2 8
I 6
PM
DM
输出样例：
-10
6
 */

#include <iostream>

const int N = 100010;

using namespace std;

int h[N];   // 堆
int hp[N];  // hp[k] 存储堆中第k个点是第几个插入的
int ph[N];  // ph[k] 第k个插入点在堆中的位置
int sz;     // 当前堆大小
int idx;    // 第几个点

// 堆交换
void heapSwap(int a, int b)
{
    swap(ph[hp[a]], ph[hp[b]]);
    swap(hp[a], hp[b]);
    swap(h[a], h[b]);
}

// 下沉
void down(int x)
{
    int t = x;

    int l = x * 2;
    int r = l + 1;

    if (l <= sz && h[l] < h[t]) {
        t = l;
    }

    if (r <= sz && h[r] < h[t]) {
        t = r;
    }

    if (t != x) {
        heapSwap(t, x);
        down(t);
    }
}

// 上浮
void up(int x)
{
    while (x / 2 && h[x / 2] > h[x]) {
        heapSwap(x / 2, x);
        x /= 2;
    }
}

int main(int argc, char const* argv[])
{
    int n = 0;
    cin >> n;

    while (n-- > 0) {
        string op = "";
        cin >> op;

        int k = 0, x = 0;
        if (op == "I") {
            cin >> x;

            sz++;
            idx++;
            h[sz] = x;
            hp[sz] = idx;
            ph[idx] = sz;

            up(sz);
        }
        else if (op == "PM") {
            cout << h[1] << endl;
        }
        else if (op == "DM") {
            heapSwap(1, sz);
            sz--;
            down(1);
        }
        else if (op == "D") {
            cin >> k;
            k = ph[k];  // 注:需要提前保存ph[k] 因为在交换后该值会被修改
            heapSwap(k, sz);
            sz--;
            up(k);
            down(k);
        }
        else if (op == "C") {
            cin >> k >> x;
            k = ph[k];
            h[k] = x;

            up(k);
            down(k);
        }
    }

    return 0;
}
