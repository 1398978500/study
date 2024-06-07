/*
给定一个大小为 n 的数组 nums ，返回其中的多数元素。
    多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。

示例 1：

输入：nums = [3,2,3]
输出：3
示例 2：

输入：nums = [2,2,1,1,1,2,2]
输出：2

*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int num = 0;
        int count = 0;
        for(int i : nums) {
            if(i == num) {
                count++;
            }else {
                count--;
                if(count < 0) {
                    num = i;
                    count = 1;
                }
            }
        }

        return num;
    }
};

int main() {
    vector<int> v{2,2,1,1,1,2,2};
    Solution s;
    cout << s.majorityElement(v) << endl;

    return 0;
}

