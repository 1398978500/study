/*
假定有一个无限长的数轴，数轴上每个坐标上的数都是 0。

现在，我们首先进行 n 次操作，每次操作将某一位置 x 上的数加 c。

接下来，进行 m 次询问，每个询问包含两个整数 l 和 r，你需要求出在区间 [l,r] 之间的所有数的和。

输入格式
第一行包含两个整数 n 和 m。

接下来 n 行，每行包含两个整数 x 和 c。

再接下来 m 行，每行包含两个整数 l 和 r。

输出格式
共 m 行，每行输出一个询问中所求的区间内数字和。

数据范围
−10^9≤x≤10^9,
1≤n,m≤10^5,
−10^9≤l≤r≤10^9,
−10000≤c≤10000
输入样例：
3 3
1 2
3 6
7 5
1 3
4 6
7 8
输出样例：
8
0
5
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 数的范围很大  但是需要输入的数 为  (n + m * 2)  n,m都取最大值 则最多有300000个数
const int N = 300010;

vector<int> vAlls;            // 所有需要离散化的数
vector<pair<int, int>> vAdd;  // 所有增加操作
vector<pair<int, int>> vOp;   // 所有要查询的操作

int aSrc[N];  // 映射后的原数组
int aSum[N];  // aSrc的前缀和

// 找到x在aSrc中的下标  即映射
int find(int x)
{
    int l = 0, r = vAlls.size() - 1;

    while (l < r) {
        int mid = l + r >> 1;

        if (vAlls[mid] < x) {
            l = mid + 1;
        }
        else {
            r = mid;
        }
    }

    return r + 1;  // 求前缀和时从1开始更方便 所以+1
}

int main(int argc, char const* argv[])
{
    int n = 0, m = 0;
    cin >> n >> m;

    // 增加操作输入
    while (n-- > 0) {
        int x = 0, c = 0;
        cin >> x >> c;

        vAlls.emplace_back(x);

        vAdd.emplace_back(x, c);
    }

    // 查询操作输入
    while (m-- > 0) {
        int l = 0, r = 0;
        cin >> l >> r;

        vAlls.emplace_back(l);
        vAlls.emplace_back(r);

        vOp.emplace_back(l, r);
    }

    // 对vAll数组进行去重并排序
    sort(vAlls.begin(), vAlls.end());
    vAlls.erase(unique(vAlls.begin(), vAlls.end()), vAlls.end());

    // 增加操作
    for (auto& item : vAdd) {
        int iIndex = find(item.first);
        aSrc[iIndex] += item.second;
    }

    // 求前缀和
    for (int i = 1; i <= vAlls.size(); i++) { aSum[i] = aSrc[i] + aSum[i - 1]; }

    // 求区间和
    for (auto& item : vOp) {
        int l = find(item.first);
        int r = find(item.second);

        cout << aSum[r] - aSum[l - 1] << endl;
    }

    return 0;
}
