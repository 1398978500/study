/*
给定一个长度为 n 的整数数列，以及一个整数 k，请用快速选择算法求出数列从小到大排序后的第 k 个数。

输入格式
第一行包含两个整数 n 和 k。

第二行包含 n 个整数（所有整数均在 1∼109 范围内），表示整数数列。

输出格式
输出一个整数，表示数列的第 k 小数。

数据范围
1≤n≤100000,
1≤k≤n

输入样例：
5 3
2 4 1 5 3
输出样例：
3
*/

#include <iostream>

using namespace std;

const int N = 100010;
int arr[N];

int kThNumber(int arr[], int l, int r, int k)
{
    if (l == r) { return arr[l]; }

    int num = arr[l + r >> 1];
    int i = l - 1, j = r + 1;

    while (i < j) {
        // 从左 找到大于等于num的数
        while (arr[++i] < num) { ; }

        // 从右 找到小于等于num的数
        while (arr[--j] > num) { ; }

        // 将找到的两数交换
        if (i < j) { swap(arr[i], arr[j]); }
    }  // 循环结束后 将数组分为两个区间 第一个区间的数都小于等于x 第二个区间的数都大于等于x

    int tmp = j - l + 1;  // 第一个区间的数个数

    // 如果 第一个区间的数个数 大于等于 k 则第k小的数在第一个区间中
    if (tmp >= k) { return quickSort(arr, l, j, k); }

    // 否则在第二个区间 并且第k小的数在第二个区间变为 第k - tmp 小的数
    return quickSort(arr, j + 1, r, k - tmp);
}

int main(int argc, char const* argv[])
{
    int n = 0, k = 0;
    cin >> n >> k;
    for (int i = 0; i < n; i++) { cin >> arr[i]; }

    cout << kThNumber(arr, 0, n - 1, k) << endl;
    return 0;
}
