/*
给定你一个长度为 n 的整数数列。

请你使用快速排序对这个数列按照从小到大进行排序。

并将排好序的数列按顺序输出。

输入格式
输入共两行，第一行包含整数 n。
第二行包含 n 个整数（所有整数均在 1∼10^9 范围内），表示整个数列。

输出格式
输出共一行，包含 n 个整数，表示排好序的数列。

数据范围
1≤n≤100000

输入样例：
5
3 1 2 4 5
输出样例：
1 2 3 4 5
*/

#include <iostream>

using namespace std;

const int N = 100010;
int arr[N];

void quickSort(int arr[], int l, int r)
{
    if (l == r) {
        return;
    }

    int num = arr[l + r >> 1];
    int i = l - 1, j = r + 1;

    while (i < j) {
        // 从左 找到大于等于num的数
        while (arr[++i] < num) { ; }

        // 从右 找到小于等于num的数
        while (arr[--j] > num) { ; }

        // 将找到的两数交换
        if (i < j) {
            swap(arr[i], arr[j]);
        }
    }  // 循环结束后 将数组分为两个区间 第一个区间的数都小于等于x 第二个区间的数都大于等于x

    // 递归处理 两个区间
    quickSort(arr, l, j);
    quickSort(arr, j + 1, r);
}

int main(int argc, char const* argv[])
{
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; i++) { cin >> arr[i]; }

    quickSort(arr, 0, n - 1);

    for (int i = 0; i < n; i++) { cout << arr[i] << " "; }
    cout << endl;

    return 0;
}
