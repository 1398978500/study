/*
给定一组非负整数 nums，重新排列每个数的顺序（每个数不可拆分）
    使之组成一个最大的整数。
注意：输出结果可能非常大，所以你需要返回一个字符串而不是整数。

示例 1：

输入：nums = [10,2]
输出："210"
示例 2：

输入：nums = [3,30,34,5,9]
输出："9534330"
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [](int a, int b){

            string ab = to_string(a) + to_string(b);
            string ba = to_string(b) + to_string(a);
            return ab > ba;
        });

        string res;
        for(int i : nums) {
            if(res.length == 0 && i == 0) {
                continue;
            }
            res += to_string(i);
        }
        if(res == "") {
            res = "0";
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> v{432,43243};
    cout << s.largestNumber(v) << endl;
    return 0;
}

