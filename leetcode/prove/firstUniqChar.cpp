/*
在字符串 s 中找出第一个只出现一次的字符。如果没有，返回一个单空格。 s 只包含小写字母。

示例 1:

输入：s = "abaccdeff"
输出：'b'
示例 2:

输入：s = "" 
输出：' '
 

限制：

0 <= s 的长度 <= 50000
*/
class Solution {
public:
    char firstUniqChar(string s) {
        unordered_map<char, int> umap;

        for(auto &c:s) {
            umap[c]++;
        }

        char res = ' ';
        for(auto &c:s) {
            if(umap[c] == 1) {
                res = c;
                break;
            } 
        }

        return res;
    }
};
