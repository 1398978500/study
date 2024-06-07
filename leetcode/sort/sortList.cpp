/*
给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。

输入：head = [4,2,1,3]
输出：[1,2,3,4]

输入：head = [-1,5,3,4,0]
输出：[-1,0,3,4,5]

输入：head = []
输出：[]

链表中节点的数目在范围 [0, 5 * 104] 内
-105 <= Node.val <= 105

进阶：你可以在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？
*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
#ifdef GUANFANG
    // 官方题解
    ListNode* sortList(ListNode* head)
    {
        if (head == nullptr) {
            return head;
        }
        int length = 0;
        ListNode* node = head;
        while (node != nullptr) {
            length++;
            node = node->next;
        }
        ListNode* dummyHead = new ListNode(0, head);
        for (int subLength = 1; subLength < length; subLength <<= 1) {
            ListNode *prev = dummyHead, *curr = dummyHead->next;
            while (curr != nullptr) {
                ListNode* head1 = curr;
                for (int i = 1; i < subLength && curr->next != nullptr; i++) {
                    curr = curr->next; 
                }
                ListNode* head2 = curr->next;
                curr->next = nullptr;
                curr = head2;
                for (int i = 1; i < subLength && curr != nullptr && curr->next != nullptr; i++) {
                    curr = curr->next;
                }
                ListNode* next = nullptr;
                if (curr != nullptr) {
                    next = curr->next;
                    curr->next = nullptr;
                }
                ListNode* merged = merge(head1, head2);
                prev->next = merged;
                while (prev->next != nullptr) {
                    prev = prev->next;
                }
                curr = next;
            }
        }
        return dummyHead->next;
    }

    ListNode* merge(ListNode* head1, ListNode* head2)
    {
        ListNode* dummyHead = new ListNode(0);
        ListNode *temp = dummyHead, *temp1 = head1, *temp2 = head2;
        while (temp1 != nullptr && temp2 != nullptr) {
            if (temp1->val <= temp2->val) {
                temp->next = temp1;
                temp1 = temp1->next;
            }
            else {
                temp->next = temp2;
                temp2 = temp2->next;
            }
            temp = temp->next;
        }
        if (temp1 != nullptr) {
            temp->next = temp1;
        }
        else if (temp2 != nullptr) {
            temp->next = temp2;
        }
        return dummyHead->next;
    }

#else
    ListNode* sortList(ListNode* head)
    {
        mergeSort(&head);

        return head;
    }

    void mergeSort(ListNode** headRef)
    {
        auto head = *headRef;
        if (!head || !head->next) {
            return;
        }

        auto slow = head;
        auto fast = head->next;
        while (fast) {
            fast = fast->next;
            if (fast) {
                fast = fast->next;
                slow = slow->next;
            }
        }

        // 将链表拆成两个
        auto first = head;
        auto second = slow->next;
        slow->next = nullptr;

        // 递归拆分
        mergeSort(&first);
        mergeSort(&second);

        // 合并两个有序链表
        *headRef = sortedMerge(first, second);
    }

    ListNode* sortedMerge(ListNode* first, ListNode* second)
    {
        if (!first) {
            return second;
        }

        if (!second) {
            return first;
        }

        ListNode* dummyHead = new ListNode();
        ListNode* tmp = dummyHead;
        while (first && second) {
            if (first->val <= second->val) {
                tmp->next = first;

                first = first->next;
            }
            else {
                tmp->next = second;

                second = second->next;
            }

            tmp = tmp->next;
        }

        if (first) {
            tmp->next = first;
        }

        if (second) {
            tmp->next = second;
        }

        auto head = dummyHead->next;
        delete dummyHead;

        return head;
    }
#endif
};
