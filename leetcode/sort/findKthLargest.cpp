/*
给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。

请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。

 

示例 1:

输入: [3,2,1,5,6,4], k = 2
输出: 5
示例 2:

输入: [3,2,3,1,2,4,5,5,6], k = 4
输出: 4
 

提示：

1 <= k <= nums.length <= 10^5
-104 <= nums[i] <= 10^4

 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        return quickSort(nums, 0, nums.size() - 1, k);
    }

    int quickSort(vector<int>& nums, int l, int r, int k) {
        if(l >= r) {
            return nums[l];
        }

        int num = nums[l + (r - l >> 1)];
        int i = l - 1, j = r + 1;
        while(i < j) {
            while(nums[++i] > num);
            while(nums[--j] < num);
            if(i < j) {
                swap(nums[i], nums[j]);
            }
        }

        // [l, j], [j+1,r]
        int lNums = j - l + 1;
        if(lNums >= k) {
            return quickSort(nums, l, j, k);
        }
        return quickSort(nums, j + 1, r, k - lNums);
    }
};

int main(int argc, char* argv[]) {
    Solution s;
    vector<int> v{3,2,1,5,6,4};
    cout << s.findKthLargest(v, 2) << endl;

    return 0;
}


