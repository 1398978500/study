/*
给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。

注意：若 s 和 t 中每个字符出现的次数都相同，则称 s 和 t 互为字母异位词。

示例 1:

输入: s = "anagram", t = "nagaram"
输出: true
示例 2:

输入: s = "rat", t = "car"
输出: false

提示:

1 <= s.length, t.length <= 5 * 10^4
s 和 t 仅包含小写字母

进阶: 如果输入字符串包含 unicode 字符怎么办？你能否调整你的解法来应对这种情况？
 */

#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.length() != t.length()) {
            return false;
        }

        unordered_map<int, int> ump;
        for(char c : s) {
            ump[c]++;
        }

        for(char c : t) {
            ump[c]--;
        }

        for(auto &item : ump) {
            if(item.first != 0) {
                return false;
            }
        }

        return true;
    }
};

int main(int argc, char* argv[]) {
    string s1 = "cat";
    string s2 = "rat";
    Solution s;
    cout << s.isAnagram(s1, s2) << endl;

    return 0;
}


