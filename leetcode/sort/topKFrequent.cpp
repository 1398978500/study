/*
给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。

示例 1:
输入: nums = [1,1,1,2,2,3], k = 2
输出: [1,2]

示例 2:
输入: nums = [1], k = 1
输出: [1]


提示：
1 <= nums.length <= 10^5
k 的取值范围是 [1, 数组中不相同的元素的个数]
题目数据保证答案唯一，换句话说，数组中前 k 个高频元素的集合是唯一的

进阶：你所设计算法的时间复杂度 必须 优于 O(n log n) ，其中 n 是数组大小。
 */

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
    // 用桶
    vector<int> useBucket(unordered_map<int, int> &umCount, int k) {
        vector<int> vRet;


        return vRet;
    }

    // 使用堆
    vector<int> useQueue(unordered_map<int, int> &umCount, int k) {
        vector<int> vRet;

        priority_queue<pair<int, int>> pq;

        for(auto &item : umCount) {
            pq.emplace(item.second, item.first);
        }

        while(k--) {
            vRet.push_back(pq.top().second);
            pq.pop();
        }

        return vRet;
    }

    // 用vector 排序
    vector<int> useSort(unordered_map<int, int> &umCount, int k) {
        vector<int> vRet;
        vector<pair<int, int>> vNumCount;
        for(auto &item : umCount) {
            vNumCount.emplace_back(item);
        }


        sort(vNumCount.begin(), vNumCount.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
                return a.second > b.second;
            });

        for(int i = 0; i < k; i++) {
            if(vNumCount.size() <= i) {
                break;
            }
            vRet.push_back(vNumCount[i].first);
        }

        return vRet;
    }

    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> umCount;

        for(int i : nums) {
            umCount[i]++;
        }


       return useBucket(umCount, k);
       //return useQueue(umCount, k);
       //return useSort(umCount, k);
    }
};

int main(int argc, char* argv[]) {
    Solution s;
    vector<int> v{1,1,1,2,2,3};
    auto res = s.topKFrequent(v, 2);

    for(int i: res) {
        cout << i << "  ";
    }
    cout << endl;
    return 0;
}


