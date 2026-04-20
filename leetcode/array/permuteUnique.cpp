/**
 * 给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。



示例 1：

输入：nums = [1,1,2]
输出：
[[1,1,2],
 [1,2,1],
 [2,1,1]]
示例 2：

输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]


提示：

1 <= nums.length <= 8
-10 <= nums[i] <= 10
 */

class Solution {
private:
    vector<vector<int>> res;

    vector<int> index_vector;

    vector<int> one_res;

public:
    void dfs(vector<int>& nums, int n)
    {
        if (n == nums.size()) {
            res.emplace_back(one_res);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            // 过滤用过的
            if (index_vector[i] || (i != 0 && nums[i] == nums[i - 1] && !index_vector[i - 1])) {
                continue;
            }

            one_res[n] = nums[i];
            index_vector[i] = 1;
            dfs(nums, n + 1);
            index_vector[i] = 0;
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums)
    {
        sort(nums.begin(), nums.end());
        one_res.resize(nums.size());
        index_vector.resize(nums.size());

        dfs(nums, 0);

        return res;
    }
};