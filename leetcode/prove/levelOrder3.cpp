/*
请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行以此类推。

 

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
  [20,9],
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

        int iLevel = 0; // 记录第几层 根为第0层
        while(!qNode.empty()) {
            int len = qNode.size();
            vector<int> vLevel(len, 0);

            for(int i = 0; i < len; i++) {
                int index = i;

                // 奇数层则倒序
                if((iLevel & 1) == 1) {
                    index = len - 1 - i;
                }

                // 记录当前层
                auto tmp = qNode.front();
                qNode.pop();
                vLevel[index] = (tmp->val);

                // 添加下一层节点
                if(tmp->left != nullptr) {
                    qNode.emplace(tmp->left);
                }

                if(tmp->right != nullptr) {
                    qNode.emplace(tmp->right);
                }
            }

            vRes.emplace_back(vLevel);
            iLevel++;
        }
        return vRes;
    }
};
