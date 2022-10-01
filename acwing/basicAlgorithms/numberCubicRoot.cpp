/*
给定一个浮点数 n，求它的三次方根。

输入格式
共一行，包含一个浮点数 n。

输出格式
共一行，包含一个浮点数，表示问题的解。

注意，结果保留 6 位小数。

数据范围
−10000≤n≤10000
输入样例：
1000.00
输出样例：
10.000000
*/

#include <iostream>

using namespace std;

int main(int argc, char const* argv[])
{
    double n = 0;
    cin >> n;

    double l = -10000, r = 10000;

    // 跳出循环的条件需要比题目要求精度多2位小数才保险
    while (r - l > 1e-8) {
        double mid = (l + r) / 2;

        if (mid * mid * mid >= n) {
            r = mid;
        }
        else {
            l = mid;
        }
    }

    printf("%.6lf\n", l);

    return 0;
}
