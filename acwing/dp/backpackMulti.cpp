/*
有 N 种物品和一个容量是 V  的背包。

第 i   种物品最多有 si 件，每件体积是 vi ，价值是 wi

求解将哪些物品装入背包，可使物品体积总和不超过背包容量，且价值总和最大。输出最大价值。

输入格式
第一行两个整数，N，V，用空格隔开，分别表示物品种数和背包容积。

接下来有 N 行，每行三个整数 vi,wi,si，用空格隔开，分别表示第 i 种物品的体积、价值和数量。

输出格式
输出一个整数，表示最大价值。

数据范围
 0<N,V≤100

 0<vi,wi,si≤100
 输入样例
 4 5
 1 2 3
 2 4 1
 3 4 3
 4 5 2
 输出样例：
 10

*/

#include <iostream>

const int N = 110;

int v[N];
int w[N];
int s[N];
int f[N];

using namespace std;

int main(int argc, char* argv[]) {
    int n, V;
    cin >> n >> V;

    for(int i = 1; i <= n; i++) {
        cin >> v[i] >> w[i] >> s[i];
    }

    for(int i = 1; i <= n; i++) {
        // for(int j = v[i]; j <= V; j++) {
        // 变成一维数组必须逆序,否则会把数量超出的情况计算在内
        for(int j = V; j >= v[i]; j--) {
            for(int k = 0; k <= s[i] && k * v[i] <= j; k++) {
                // 二维
                // f[i][j] = max(f[i][j], f[i - 1][j - k * v[i]] + k * w[i]);
                // 一维数组
                f[j] = max(f[j], f[j - k * v[i]] + k * w[i]);
            }
        }
    }

    cout << f[V] << endl;

    return 0;
}

