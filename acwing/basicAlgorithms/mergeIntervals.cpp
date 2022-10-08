/*
给定 n 个区间 [li,ri]，要求合并所有有交集的区间。

注意如果在端点处相交，也算有交集。

输出合并完成后的区间个数。

例如：[1,3] 和 [2,6] 可以合并为一个区间 [1,6]。

输入格式
第一行包含整数 n。

接下来 n 行，每行包含两个整数 l 和 r。

输出格式
共一行，包含一个整数，表示合并区间完成后的区间个数。

数据范围
1≤n≤100000,
−10^9≤li≤ri≤10^9
输入样例：
5
1 2
2 4
5 6
7 8
7 9
输出样例：
3
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> vInter;

void merge(vector<pair<int, int>>& vInter)
{
    if (vInter.empty()) {
        return;
    }

    vector<pair<int, int>> vRes;

    sort(vInter.begin(), vInter.end());

    int iStart = -2e9, iEnd = -2e9;
    for (auto& item : vInter) {
        // 区间相交
        if (item.first > iEnd) {
            if (iStart != -2e9) {
                vRes.emplace_back(iStart, iEnd);
            }

            iStart = item.first;
            iEnd = item.second;
        }
        // 不相交
        else {
            iEnd = max(item.second, iEnd);
        }
    }

    // 最后一个加到结果中
    if (iStart != -2e9) {
        vRes.emplace_back(iStart, iEnd);
    }

    vInter = vRes;
}

int main(int argc, char const* argv[])
{
    int n = 0;
    cin >> n;

    while (n-- > 0) {
        int l = 0, r = 0;
        cin >> l >> r;

        vInter.emplace_back(l, r);
    }

    // 区间合并
    merge(vInter);

    cout << vInter.size() << endl;

    return 0;
}
