/*
输入一个长度为 n 的整数序列。

接下来输入 m 个操作，每个操作包含三个整数 l,r,c，表示将序列中 [l,r] 之间的每个数加上 c。

请你输出进行完所有操作后的序列。

输入格式
第一行包含两个整数 n 和 m。

第二行包含 n 个整数，表示整数序列。

接下来 m 行，每行包含三个整数 l，r，c，表示一个操作。

输出格式
共一行，包含 n 个整数，表示最终序列。

数据范围
1≤n,m≤100000,
1≤l≤r≤n,
−1000≤c≤1000,
−1000≤整数序列中元素的值≤1000
输入样例：
6 3
1 2 2 1 2 1
1 3 1
3 5 1
1 6 1
输出样例：
3 4 5 3 4 2
*/

#include <iostream>

using namespace std;

const int N = 100010;
int dif[N];  // 存与上一个的差

// 当[l,r]范围内的数均增加 c 则只有 l 与 (r+1) 的差发生了变化
void insert(int arr[], int l, int r, int c)
{
    arr[l] += c;
    arr[r + 1] -= c;
}

int main(int argc, char const* argv[])
{
    int n = 0, m = 0;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        int tmp = 0;
        cin >> tmp;

        // 认为是[i,i]范围内的数增加tmp
        insert(dif, i, i, tmp);
    }

    while (m-- > 0) {
        int l = 0, r = 0, c = 0;
        cin >> l >> r >> c;

        insert(dif, l, r, c);
    }

    for (int i = 1; i <= n; i++) {
        dif[i] += dif[i - 1];
        cout << dif[i] << " ";
    }
    cout << endl;

    return 0;
}
