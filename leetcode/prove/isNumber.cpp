/*
请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。

数值（按顺序）可以分成以下几个部分：

若干空格
一个 小数 或者 整数
（可选）一个 'e' 或 'E' ，后面跟着一个 整数
若干空格
小数（按顺序）可以分成以下几个部分：

（可选）一个符号字符（'+' 或 '-'）
下述格式之一：
至少一位数字，后面跟着一个点 '.'
至少一位数字，后面跟着一个点 '.' ，后面再跟着至少一位数字
一个点 '.' ，后面跟着至少一位数字
整数（按顺序）可以分成以下几个部分：

（可选）一个符号字符（'+' 或 '-'）
至少一位数字
部分数值列举如下：

["+100", "5e2", "-123", "3.1416", "-1E-16", "0123"]
部分非数值列举如下：

["12e", "1a3.14", "1.2.3", "+-5", "12e+5.4"]
*/

class Solution {
public:
    bool isNumber(string s)
    {
        // 删除首尾空格
        int i = 0;
        while (i < s.length() && s[i] == ' ') { ++i; }
        s = s.substr(i);

        while (s.back() == ' ') { s.pop_back(); }

        bool numFlag = false;  // 是否是数字
        bool dotFlag = false;  // 是否出现过'.'
        bool eFlag = false;    // 是否出现过'e/E'

        for (int i = 0; i < s.length(); ++i) {
            // 出现数字
            if (isdigit(s[i])) {
                numFlag = true;
            }
            // 出现了'.'时 之前不能出现过'.'和'e/E'
            else if (s[i] == '.' && !dotFlag && !eFlag) {
                dotFlag = true;
            }
            // 出现 'e/E' 之前不能出现过'e/E' 并且必须是数字
            else if ((s[i] == 'e' || s[i] == 'E') && !eFlag && numFlag) {
                eFlag = true;
                numFlag = false;
            }
            // 出现 '+'或'-' 必须时开头或者'e/E'之后
            else if ((s[i] == '+' || s[i] == '-') && (i == 0 || s[i - 1] == 'e' || s[i - 1] == 'E')) {
                continue;
            }
            else {
                return false;
            }
        }

        return numFlag;
    }
};
