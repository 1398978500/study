/*
输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有奇数在数组的前半部分，所有偶数在数组的后半部分。



示例：

输入：nums = [1,2,3,4]
输出：[1,3,2,4]
注：[3,1,2,4] 也是正确的答案之一。


提示：

0 <= nums.length <= 50000
0 <= nums[i] <= 10000
*/
class Solution {
public:
    vector<int> exchange(vector<int>& nums)
    {
        int l = -1, r = nums.size();

        while (l < r) {
            while (++l < r && (nums[l] & 1) == 1)
                ;
            while (l < --r && (nums[r] & 1) == 0)
                ;
            if (l < r) {
                swap(nums[l], nums[r]);
            }
        }

        return nums;
    }
};