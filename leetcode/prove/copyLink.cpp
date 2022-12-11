/*
请实现 copyRandomList 函数，复制一个复杂链表。在复杂链表中，每个节点除了有一个 next 指针指向下一个节点，还有一个 random 指针指向链表中的任意节点或者 null。
*/

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        // 记录原链表节点与复制节点之间的关系
        unordered_map<Node*, Node*> mRec;

        Node* tmp = head;
        // 创建节点并记录与原节点的关系
        while(tmp != nullptr) {
            Node* newNode = new Node(tmp->val);
            mRec[tmp] = newNode;
            tmp = tmp->next;
        }

        tmp = head;
        // 将复制的链表链接起来
        while(tmp != nullptr) {
            auto next = mRec[tmp->next];
            auto random = mRec[tmp->random];

            if(next != nullptr){
                mRec[tmp]->next = next;
            }

            if(random != nullptr){
                mRec[tmp]->random = random;
            }
            tmp = tmp->next;
        }

        return mRec[head];
    }
};
