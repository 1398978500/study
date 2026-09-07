/*
给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

请你设计并实现时间复杂度为 O(n) 的算法解决此问题。



示例 1：

输入：nums = [100,4,200,1,3,2]
输出：4
解释：最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4。
示例 2：

输入：nums = [0,3,7,2,5,8,4,6,0,1]
输出：9
示例 3：

输入：nums = [1,0,1,2]
输出：3


提示：

0 <= nums.length <= 105
-109 <= nums[i] <= 109
*/
class Solution {
public:
    int longestConsecutive(vector<int>& nums)
    {
        unordered_set<int> num_set;
        for (auto i : nums) { num_set.insert(i); }

        int res = 0;
        for (auto i : num_set) {
            if (num_set.count(i - 1)) {
                continue;
            }

            int longest = 1;
            int current_num = i;
            while (num_set.count(current_num + 1)) {
                current_num++;
                longest++;
            }

            res = max(res, longest);
        }

        return res;
    }
};
