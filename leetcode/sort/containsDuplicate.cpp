/*
给你一个整数数组 nums 。如果任一值在数组中出现 至少两次 ，返回 true ；如果数组中每个元素互不相同，返回 false 。
 

示例 1：

输入：nums = [1,2,3,1]
输出：true
示例 2：

输入：nums = [1,2,3,4]
输出：false
示例 3：

输入：nums = [1,1,1,3,3,4,3,2,4,2]
输出：true

 * */
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    void quickSort(vector<int>& nums, int l, int r) {
        if(l >= r) {
            return;
        }
        int mid = nums[(l + ((r - l) >> 1))];

        int i = l - 1, j = r + 1;
        while(i < j) {
            while(nums[++i] < mid) ;
            while(nums[--j] > mid) ;

            if(i < j) {
                swap(nums[i], nums[j]);
            }
        }

        quickSort(nums, l, j);
        quickSort(nums, j + 1, r);
    }

    bool containsDuplicate(vector<int>& nums) {
        // 先排序
        quickSort(nums, 0, nums.size() - 1);

        bool bRes = false;

        for(size_t i = 0; i < nums.size() - 1; i++) {
            if(nums[i] == nums[i + 1]) {
                return true;
            }
        }

        return false;
    }
};

int main() {
    vector<int> a{1,2,3,1};

    Solution s;

    if(s.containsDuplicate(a)) {
        cout << "有重复的" << endl;
    } else {
        cout << "没重复的" << endl;
    }

    for(auto i:a) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
