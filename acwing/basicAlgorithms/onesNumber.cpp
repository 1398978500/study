/*
给定一个长度为 n 的数列，请你求出数列中每个数的二进制表示中 1 的个数。

输入格式
第一行包含整数 n。

第二行包含 n 个整数，表示整个数列。

输出格式
共一行，包含 n 个整数，其中的第 i 个数表示数列中的第 i 个数的二进制表示中 1 的个数。

数据范围
1≤n≤100000,
0≤数列中元素的值≤10^9
输入样例：
5
1 2 3 4 5
输出样例：
1 1 2 1 2
*/
#include <iostream>

using namespace std;

// 找1的个数
int onesNumber(int i)
{
    int iNum = 0;
    while (i > 0) {
        i &= (i - 1);  // 此操作可消除i二进制中的最低位的1
        iNum++;
    }

    return iNum;
}

int main(int argc, char const* argv[])
{
    int n = 0;
    cin >> n;
    while (n-- > 0) {
        int i = 0;
        cin >> i;

        cout << onesNumber(i) << " ";
    }
    return 0;
}
