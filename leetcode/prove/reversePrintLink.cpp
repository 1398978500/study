/*
输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。



示例 1：

输入：head = [1,3,2]
输出：[2,3,1]


限制：

0 <= 链表长度 <= 10000
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> reversePrint(ListNode* head)
    {
        vector<int> vRes;
        if (head == nullptr) {
            return vRes;
        }

        // 先逆序
        ListNode* last = nullptr;
        auto now = head;
        while (now != nullptr) {
            auto nx = now->next;
            now->next = last;
            last = now;
            now = nx;
        }

        // 将结果保存到容器中
        while (last != nullptr) {
            vRes.emplace_back(last->val);
            last = last->next;
        }

        return vRes;
    }
};
