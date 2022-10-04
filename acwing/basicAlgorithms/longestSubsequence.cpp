/*
给定一个长度为 n 的整数序列，请找出最长的不包含重复的数的连续区间，输出它的长度。

输入格式
第一行包含整数 n。

第二行包含 n 个整数（均在 0∼10^5 范围内），表示整数序列。

输出格式
共一行，包含一个整数，表示最长的不包含重复的数的连续区间的长度。

数据范围
1≤n≤10^5
输入样例：
5
1 2 2 3 5
输出样例：
3
*/

#include <iostream>
#include <unordered_map>

using namespace std;

const int N = 100010;
int arr[N];

int main(int argc, char const* argv[])
{
    int n = 0;
    cin >> n;

    for (int i = 1; i <= n; i++) { cin >> arr[i]; }

    unordered_map<int, int> mRecord;  // 用来存储[i,j] 范围内数出现的次数
    int res = 0;

    for (int i = 1, j = 1; i <= n; i++) {
        mRecord[arr[i]]++;

        while (j <= i && mRecord[arr[i]] > 1) { mRecord[arr[j++]]--; }

        res = max(res, i - j + 1);
    }

    cout << res << endl;

    return 0;
}
