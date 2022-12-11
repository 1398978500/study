/*
一个长度为n-1的递增排序数组中的所有数字都是唯一的，并且每个数字都在范围0～n-1之内。在范围0～n-1内的n个数字中有且只有一个数字不在该数组中，请找出这个数字。



示例 1:

输入: [0,1,3]
输出: 2
示例 2:

输入: [0,1,2,3,4,5,6,7,9]
输出: 8


限制：

1 <= 数组长度 <= 10000
*/

// 解法1使用抑或
class Solution {
public:
    int missingNumber(vector<int>& nums)
    {
        int res = 0;
        for (int i = 0; i < nums.size(); i++) {
            res ^= (i + 1);
            res ^= nums[i];
        }

        return res;
    }
};

// 解法2 二分
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;

        while(l <= r) {
            int mid = l + r >> 1;
            if(mid == nums[mid]) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        return l;
    }
};
