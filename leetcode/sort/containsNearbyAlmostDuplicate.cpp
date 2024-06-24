/*
给你一个整数数组 nums 和两个整数 indexDiff 和 valueDiff 。
找出满足下述条件的下标对 (i, j)：
i != j,
abs(i - j) <= indexDiff
abs(nums[i] - nums[j]) <= valueDiff
如果存在，返回 true ；否则，返回 false 。

示例 1：
输入：nums = [1,2,3,1], indexDiff = 3, valueDiff = 0
输出：true
解释：可以找出 (i, j) = (0, 3) 。
满足下述 3 个条件：
i != j --> 0 != 3
abs(i - j) <= indexDiff --> abs(0 - 3) <= 3
abs(nums[i] - nums[j]) <= valueDiff --> abs(1 - 1) <= 0

示例 2：
输入：nums = [1,5,9,1,5,9], indexDiff = 2, valueDiff = 3
输出：false
解释：尝试所有可能的下标对 (i, j) ，均无法满足这 3 个条件，因此返回 false 。

提示：
2 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
1 <= indexDiff <= nums.length
0 <= valueDiff <= 10^9
*/

#include <vector>
#include <iostream>
#include <set>

using namespace std;

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        set<int> window;
        for(int i = 0; i < nums.size(); i++) {
            // 保持窗口中的数字满足下标要求
            if(i > indexDiff) {
                // 删掉第一个进入窗口的
                window.erase(nums[i - indexDiff - 1]);
            }

            // abs(nums[i] - nums[j]) <= valueDiff
            // 转化为 nums[i] - valueDiff <= nums[j] <= valueDiff + nums[i]
            // 查找窗口中有没有 >= nums[i] - valueDiff的数
            auto pos = window.lower_bound(nums[i] - valueDiff);
            // 能找到并且满足 <= valueDiff + nums[i]
            if(pos != window.end() && *pos <= valueDiff + nums[i]) {
                return true;
            }

            // 判断完将当前数字假如到window
            window.emplace(nums[i]);
        }

        return false;
    }
};

int main() {
    Solution s;
    vector<int> nums1 = {1, 2, 3, 1};
    int indexDiff1 = 3, valueDiff1 = 0;
    cout << (s.containsNearbyAlmostDuplicate(nums1, indexDiff1, valueDiff1) ? "true" : "false") << endl;

    vector<int> nums2 = {1, 5, 9, 1, 5, 9};
    int indexDiff2 = 2, valueDiff2 = 3;
    cout << (s.containsNearbyAlmostDuplicate(nums2, indexDiff2, valueDiff2) ? "true" : "false") << endl;

    return 0;
}
