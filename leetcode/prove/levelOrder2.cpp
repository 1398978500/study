/*
从上到下按层打印二叉树，同一层的节点按从左到右的顺序打印，每一层打印到一行。

 

例如:
给定二叉树: [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
返回其层次遍历结果：

[
  [3],
  [9,20],
  [15,7]
]
 

提示：

节点总数 <= 1000
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> vRes;
        if(root == nullptr) {
            return vRes;
        }

        queue<TreeNode*> qNode;
        qNode.emplace(root);
        while(!qNode.empty()) {
            queue<TreeNode*> qTmp;
            while(!qNode.empty()) {
                qTmp.emplace(qNode.front());
                qNode.pop();
            }
            
            vector<int> vLevel;
            while(!qTmp.empty()) {
                auto p = qTmp.front();
                qTmp.pop();
                vLevel.emplace_back(p->val);

                if(p->left != nullptr) {
                    qNode.emplace(p->left);
                }

                if(p->right != nullptr) {
                    qNode.emplace(p->right);
                }
            }

            vRes.emplace_back(vLevel);
        }

        return vRes;
    }
};
