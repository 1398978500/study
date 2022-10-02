/*
给定一个包含红色、白色和蓝色、共 n
个元素的数组 nums ，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

必须在不使用库的sort函数的情况下解决这个问题。

 

示例 1：

输入：nums = [2,0,2,1,1,0]
输出：[0,0,1,1,2,2]
示例 2：

输入：nums = [2,0,1]
输出：[0,1,2]

提示：

n == nums.length
1 <= n <= 300
nums[i] 为 0、1 或 2
*/
class Solution {
public:
    // 解法1 : 循环两次 第一次将0全部转移到数组最左 第二次将2全部转移到数组最右
    void sortColors(vector<int>& nums)
    {
        if (nums.empty())
            return;

        int l = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (0 == nums[i]) {
                swap(nums[i], nums[l++]);
            }
        }

        int r = nums.size() - 1;
        for (int i = r; i >= 0; i--) {
            if (2 == nums[i]) {
                swap(nums[i], nums[r--]);
            }
        }
    }

    // 解法2 : 循环1次
    void sortColors2(vector<int>& nums)
    {
        int i = 0;                // 标记0下标
        int j = nums.size() - 1;  // 标记2下标
        int index = 0;            // 当前处理下标

        while (index <= j) {
            if (0 == nums[index]) {
                swap(nums[i++], nums[index++]);
            }
            else if (2 == nums[index]) {
                swap(nums[j--], nums[index]);
            }
            else {
                index++;
            }
        }
    }
};