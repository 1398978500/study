/*
统计一个数字在排序数组中出现的次数。

 

示例 1:

输入: nums = [5,7,7,8,8,10], target = 8
输出: 2
示例 2:

输入: nums = [5,7,7,8,8,10], target = 6
输出: 0
*/
class Solution {
public:
    // 二分查找第一个大于target 的数下标
    int binSearch(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        // = 防止数组中只有1个数
        while(l <= r) {
            int mid = l + r >> 1;

            if(nums[mid] > target) {
                r = mid - 1;
            }else {
                l = mid + 1;
            }
        }

        return l;
    }

    int search(vector<int>& nums, int target) {
       
        return binSearch(nums, target) - binSearch(nums, target - 1);
    }
};
