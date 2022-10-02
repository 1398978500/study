/*
以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi]
。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。

示例 1：

输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
示例 2：

输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。
 

提示：

1 <= intervals.length <= 104
intervals[i].length == 2
0 <= starti <= endi <= 104
*/

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals)
    {
        vector<vector<int>> vResult;
        if (intervals.empty()) {
            return vResult;
        }

        std::sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a.size() < 2u && b.size() < 2u) {
                return true;
            }

            if (a[0] != b[0]) {
                return a[0] < b[0];
            }

            return a[1] > b[1];
        });

        for (auto& item : intervals) {
            // 判错
            if (item.size() < 2u) {
                continue;
            }

            // 第一个
            if (vResult.empty()) {
                vResult.emplace_back(item);
                continue;
            }

            auto& cur = vResult.back();

            // 当前遍历到的区间已被上一个包含
            if (item[1] <= cur[1] || item[0] == cur[0]) {
                continue;
            }

            // 与上个区间没有相交
            if (item[0] > cur[1]) {
                vResult.emplace_back(item);
            }
            // 与上个区间相交
            else {
                cur[1] = item[1];
            }
        }

        return vResult;
    }
};