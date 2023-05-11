/*
给定一个数组 nums 和滑动窗口的大小 k，请找出所有滑动窗口里的最大值。

示例:

输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
输出: [3,3,5,5,6,7]
解释:

  滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7


提示：

你可以假设 k 总是有效的，在输入数组 不为空 的情况下，1 ≤ k ≤ nums.length。
*/
class Solution {
public:
    queue<int> q;  // 窗口
    deque<int> d;  // 窗口最大值
    vector<int> maxSlidingWindow(vector<int>& nums, int k)
    {
        vector<int> res;  // 结果
        for (int i : nums) {
            q.emplace(i);

            while (!d.empty() && d.back() < i) { d.pop_back(); }
            d.emplace_back(i);

            if (q.size() >= k) {  // 窗口长度为k时 删除队头 并取最大值
                res.emplace_back(d.front());

                int last = q.front();
                q.pop();

                if (last == d.front()) {
                    d.pop_front();
                }
            }
        }

        return res;
    }
};
