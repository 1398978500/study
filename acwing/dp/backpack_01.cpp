/*
有 N 件物品和一个容量是 V 的背包。每件物品只能使用一次。
第 i 件物品的体积是 vi，价值是 wi。

求解将哪些物品装入背包，可使这些物品的总体积不超过背包容量，且总价值最大。输出最大价值。

输入格式
第一行两个整数，N，V，用空格隔开，分别表示物品数量和背包容积。
接下来有 N 行，每行两个整数 vi,wi，用空格隔开，分别表示第 i 件物品的体积和价值。

输出格式
输出一个整数，表示最大价值。

数据范围
0<N,V≤1000

0<vi,wi≤1000
输入样例
4 5
1 2
2 4
3 4
4 5
输出样例：
8
 * */

#include <iostream>

using namespace std;

const int N = 1010;

int v[N];
int w[N];
int f[N];

int main(int argc, char* argv[]) {
    int n, V;
    cin >> n >> V;

    for(int i = 1; i <= n; i++) {
        cin >> v[i] >> w[i];
    }

    for(int i = 1; i <= n; i++) {
        for(int j = V; j >= v[i]; j--) {
            // 二维数组可以缩减为一维数组,但是需要反向遍历
            // 这里缩减没问题,因为f[j] 开始遍历前存储的是上一层结果
            // f[i][j] = max(f[i][j], f[i - 1][j]);
            //
            // 这里遍历时,若从小->大遍历,f[i-1][j-v[i]]缩减为一维数组时
            // f[j-v[i]] 在使用前会被本层数据覆盖,所以从大->小遍历
            // f[i][j] = max(f[i][j], f[i - 1][j - v[i]] + w[i]);
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }

    cout << f[V] << endl;

    return 0;
}

