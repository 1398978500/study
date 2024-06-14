/*
给定一个大小为 n 的整数数组，找出其中所有出现超过 ⌊ n/3 ⌋ 次的元素。

示例 1：

输入：nums = [3,2,3]
输出：[3]
示例 2：

输入：nums = [1]
输出：[1]
示例 3：

输入：nums = [1,2]
输出：[1,2]
 

提示：

1 <= nums.length <= 5 * 104
-109 <= nums[i] <= 109

进阶：尝试设计时间复杂度为 O(n)、空间复杂度为 O(1)的算法解决此问题。

 */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
#if 0 // 解法1
        unordered_map<int, int> ump;
        for(int i : nums) {
            ump[i]++;
        }

        int iNums = nums.size() / 3;
        vector<int> vRes;
        for(auto &item : ump) {
            if(item.second > iNums) {
                vRes.emplace_back(item.first);
            }
        }

        return vRes;
#endif
        int iMaj1 = 0;
        int iMaj2 = 0;
        int iNum1 = 0;
        int iNum2 = 0;
        vector<int> vRes;

        for(int i : nums) {
            if(iNum1 > 0 && i == iMaj1) {
                iNum1++;
            } else if(iNum2 > 0 && i == iMaj2) {
                iNum2++;
            } else if(iNum1 == 0) {
                iMaj1 = i;
                iNum1++;
            } else if(iNum2 == 0) {
                iMaj2 = i;
                iNum2++;
            } else {
                iNum1--;
                iNum2--;
            }
        }

        iNum1 = 0;
        iNum2 = 0;
        for(int i : nums) {
            if(i == iMaj1) {
                iNum1++;
            } else if(i == iMaj2) {
                iNum2++;
            }
        }

        if(iNum1 > nums.size() / 3) {
            vRes.emplace_back(iMaj1);
        }

        if(iNum2 > nums.size() / 3) {
            vRes.emplace_back(iMaj2);
        }

        return vRes;
    }
};

int main(int argc, char* argv[]) {
    vector<int> nums{1,2,3,2};
    Solution s;

    vector<int> res = s.majorityElement(nums);
    for(int i : res) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}


