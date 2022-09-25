/*
给定一个长度为 n 的整数数列，请你计算数列中的逆序对的数量。

逆序对的定义如下：对于数列的第 i 个和第 j 个元素，如果满足 i<j 且 a[i]>a[j]，则其为一个逆序对；否则不是。

输入格式
第一行包含整数 n，表示数列的长度。

第二行包含 n 个整数，表示整个数列。

输出格式
输出一个整数，表示逆序对的个数。

数据范围
1≤n≤100000，
数列中的元素的取值范围 [1,10^9]。

输入样例：
6
2 3 4 5 6 1
输出样例：
5
*/

#include <iostream>

using namespace std;

const int N = 100010;
int arr[N];
int tmp[N];  // 中间数组

// 考虑最坏情况 若数组有100000并为倒序
// 则 逆序对数量 (100000+99999+99998+...+1) = (100000+1)*100000/2 约为5*10^9
// 已经超出int范围 所以使用long long
long long reversePair(int arr[], int l, int r)
{
    if (l == r) {
        return 0;
    }

    int mid = l + r >> 1;

    // 首先递归处理所有元素
    long long sum = reversePair(arr, l, mid) + reversePair(arr, mid + 1, r);
    // 递归结束后 数组前半部分和后半部分均 各自有序

    int i = l, j = mid + 1, k = l;
    // 将数组左边和右边按顺序赋值给tmp中间数组
    while (i <= mid && j <= r) {
        if (arr[i] <= arr[j]) {
            tmp[k++] = arr[i++];
        }
        else {
            // 第一个区间的数大于第二个区间的数时  则第一个区间右边所有的数都大于当前第二个区间的数 并且都组成逆序对
            sum += mid - i + 1;
            tmp[k++] = arr[j++];
        }
    }

    while (i <= mid) { tmp[k++] = arr[i++]; }

    while (j <= r) { tmp[k++] = arr[j++]; }

    // 将tmp数组写回arr
    for (k = l; k <= r; k++) { arr[k] = tmp[k]; }

    return sum;
}

int main(int argc, char const* argv[])
{
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; i++) { cin >> arr[i]; }

    cout << reversePair(arr, 0, n - 1) << endl;
    return 0;
}
