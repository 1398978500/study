/*
给定两个升序排序的有序数组 A 和 B，以及一个目标值 x。

数组下标从 0 开始。

请你求出满足 A[i]+B[j]=x 的数对 (i,j)。

数据保证有唯一解。

输入格式
第一行包含三个整数 n,m,x，分别表示 A 的长度，B 的长度以及目标值 x。

第二行包含 n 个整数，表示数组 A。

第三行包含 m 个整数，表示数组 B。

输出格式
共一行，包含两个整数 i 和 j。

数据范围
数组长度不超过 10^5。
同一数组内元素各不相同。
1≤数组元素≤10^9
输入样例：
4 5 6
1 2 4 7
3 4 6 8 9
输出样例：
1 1
*/

#include <iostream>

using namespace std;

const int N = 100010;

int arr1[N], arr2[N];

int main(int argc, char const* argv[])
{
    int n = 0, m = 0, x = 0;
    cin >> n >> m >> x;
    for (int i = 0; i < n; i++) { cin >> arr1[i]; }

    for (int i = 0; i < m; i++) { cin >> arr2[i]; }

    int i = 0, j = m - 1;

    // 由于两数组均升序 从左向右遍历数组1 从右向左遍历数组2
    // 若当前两数和大于目标值 则数组2下标左移 否则数组1下标右移
    while (i < n && j >= 0) {
        int iSum = arr1[i] + arr2[j];
        if (iSum == x) {
            cout << i << " " << j << endl;
            break;
        }

        if (iSum > x) {
            j--;
        }
        else {
            i++;
        }
    }

    return 0;
}
