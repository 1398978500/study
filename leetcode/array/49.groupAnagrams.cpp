/**
 * 给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。
示例 1:

输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]

输出: [["bat"],["nat","tan"],["ate","eat","tea"]]

解释：

在 strs 中没有字符串可以通过重新排列来形成 "bat"。
字符串 "nat" 和 "tan" 是字母异位词，因为它们可以重新排列以形成彼此。
字符串 "ate" ，"eat" 和 "tea" 是字母异位词，因为它们可以重新排列以形成彼此。
示例 2:

输入: strs = [""]

输出: [[""]]

示例 3:

输入: strs = ["a"]

输出: [["a"]]



提示：

1 <= strs.length <= 104
0 <= strs[i].length <= 100
strs[i] 仅包含小写字母
 */

class Solution {
public:
    string genKey(string str)
    {
        string key(26, 0);
        for (char c : s) key[c - 'a']++;  // char 存 0~100 的计数，安全
        return key;
    }

    vector<vector<string>> groupAnagrams(vector<string>& strs)
    {
        vector<vector<string>> res;

        unordered_map<string, vector<string>> str_map;
        for (auto& str : strs) { str_map[genKey(str)].emplace_back(str); }

        for (auto& item : str_map) { res.emplace_back(item.second); }

        return res;
    }
};