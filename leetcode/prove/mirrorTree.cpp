/*
请完成一个函数，输入一个二叉树，该函数输出它的镜像。

例如输入：

     4

   /   \

  2     7

 / \   / \

1   3 6   9
镜像输出：

     4

   /   \

  7     2

 / \   / \

9   6 3   1



示例 1：

输入：root = [4,2,7,1,3,6,9]
输出：[4,7,2,9,6,3,1]


限制：

0 <= 节点个数 <= 1000
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
    TreeNode* mirrorTree(TreeNode* root)
    {
        if (root == nullptr) {
            return root;
        }

        queue<TreeNode*> qNode;
        qNode.emplace(root);

        // 遍历树的所有节点 并交换各节点的左右子节点
        while (!qNode.empty()) {
            auto cur = qNode.front();
            qNode.pop();

            if (cur->left != nullptr) {
                qNode.emplace(cur->left);
            }

            if (cur->right != nullptr) {
                qNode.emplace(cur->right);
            }

            swap(cur->left, cur->right);
        }

        return root;
    }
};
