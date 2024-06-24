/*
给定一个无序的数组 nums，返回 数组在排序之后，相邻元素之间最大的差值 。如果数组元素个数小于 2，则返回 0 。
您必须编写一个在「线性时间」内运行并使用「线性额外空间」的算法。

示例 1:
输入: nums = [3,6,9,1]
输出: 3
解释: 排序后的数组是 [1,3,6,9], 其中相邻元素 (3,6) 和 (6,9) 之间都存在最大差值 3。

示例 2:
输入: nums = [10]
输出: 0
解释: 数组元素个数小于 2，因此返回 0。


提示:
1 <= nums.length <= 10^5
0 <= nums[i] <= 10^9
*/

#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
#if 1
    // 基于桶排序
    int maximumGap(vector<int>& nums) {
        if (nums.size() < 2) return 0;

        int minNum = *min_element(nums.begin(), nums.end());
        int maxNum = *max_element(nums.begin(), nums.end());
        int bucketSize = max(1, (maxNum - minNum) / ((int)nums.size() - 1));
        int bucketNum = (maxNum - minNum) / bucketSize + 1;
        vector<vector<int>> buckets(bucketNum);

        for (int num : nums) {
            int bucketIdx = (num - minNum) / bucketSize;
            if (buckets[bucketIdx].empty()) {
                buckets[bucketIdx].resize(2);
                buckets[bucketIdx][0] = num; // store min
                buckets[bucketIdx][1] = num; // store max
            } else {
                buckets[bucketIdx][0] = min(buckets[bucketIdx][0], num);
                buckets[bucketIdx][1] = max(buckets[bucketIdx][1], num);
            }
        }

        int maxGap = 0;
        int previousMax = minNum;
        for (const auto& bucket : buckets) {
            if (!bucket.empty()) {
                maxGap = max(maxGap, bucket[0] - previousMax);
                previousMax = bucket[1];
            }
        }

        return maxGap;
    }
#else
    // 基数排序
    int maximumGap(vector<int>& nums) {
        if (nums.size() < 2) return 0;

        // 找到最大值
        int maxVal = *max_element(nums.begin(), nums.end());

        // 用于基数排序的桶
        vector<int> bucket(nums.size(), 0);
        int exp = 1;  // 代表位数中的10的幂次

        // 基数排序
        while (maxVal / exp > 0) {
            vector<int> count(10, 0);

            // 计数排序的计数阶段
            for (int num : nums) {
                count[(num / exp) % 10]++;
            }

            // 累加计数数组
            for (int i = 1; i < 10; i++) {
                count[i] += count[i - 1];
            }

            // 根据计数数组进行排序
            for (int i = nums.size() - 1; i >= 0; i--) {
                bucket[--count[(nums[i] / exp) % 10]] = nums[i];
            }

            // 将排序好的数据写回原数组
            for (int i = 0; i < nums.size(); i++) {
                nums[i] = bucket[i];
            }

            // 移动到下一个位
            exp *= 10;
        }

        // 计算最大间隙
        int maxGap = 0;
        for (int i = 1; i < nums.size(); i++) {
            maxGap = max(maxGap, nums[i] - nums[i - 1]);
        }

        return maxGap;
    }
#endif
};

int main() {
    Solution s;
    vector<int> v{4,10,2,1};
    cout << s.maximumGap(v) << endl;
    return 0;
}
