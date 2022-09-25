/*
给定你一个长度为 n 的整数数列。

请你使用归并排序对这个数列按照从小到大进行排序。

并将排好序的数列按顺序输出。

输入格式
输入共两行，第一行包含整数 n。

第二行包含 n 个整数（所有整数均在 1∼109 范围内），表示整个数列。

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
int tmp[N];  // 中间数组

void mergeSort(int arr[], int l, int r)
{
    if (l == r) {
        return;
    }

    int mid = l + r >> 1;

    // 首先递归处理所有元素
    mergeSort(arr, l, mid);
    mergeSort(arr, mid + 1, r);
    // 递归结束后 数组前半部分和后半部分均 各自有序

    int i = l, j = mid + 1, k = l;
    // 将数组左边和右边按顺序赋值给tmp中间数组
    while (i <= mid && j <= r) {
        if (arr[i] <= arr[j]) {
            tmp[k++] = arr[i++];
        }
        else {
            tmp[k++] = arr[j++];
        }
    }

    while (i <= mid) { tmp[k++] = arr[i++]; }

    while (j <= r) { tmp[k++] = arr[j++]; }

    // 将tmp数组写回arr
    for (k = l; k <= r; k++) { arr[k] = tmp[k]; }
}

int main(int argc, char const* argv[])
{
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; i++) { cin >> arr[i]; }

    mergeSort(arr, 0, n - 1);

    for (int i = 0; i < n; i++) { cout << arr[i] << " "; }
    cout << endl;
    return 0;
}
