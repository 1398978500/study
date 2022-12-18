/*
给定一个数字，我们按照如下规则把它翻译为字符串：0 翻译成 “a” ，1 翻译成 “b”，……，11 翻译成 “l”，……，25 翻译成 “z”。一个数字可能有多个翻译。请编程实现一个函数，用来计算一个数字有多少种不同的翻译方法。

 

示例 1:

输入: 12258
输出: 5
解释: 12258有5种不同的翻译，分别是"bccfi", "bwfi", "bczi", "mcfi"和"mzi"
 

提示：

0 <= num < 2^31
*/
class Solution {
public:
    // 跳台阶问题变形
    int translateNum(int num) {
        int a = 0, b = 1;
        int last = 0;
        while(num > 0) {
            int tmp = num % 10;

            int add = b;

            // 只有这种情况可以跳两阶
            if(tmp == 1 || (tmp == 2 && last < 6)) {
                add += a;
            }

            a = b;
            b = add;
            last = tmp;

            num /= 10;
        }

        return b;
    }
};
