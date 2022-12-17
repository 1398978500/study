/*
请实现一个函数，用来判断一棵二叉树是不是对称的。如果一棵二叉树和它的镜像一样，那么它是对称的。

例如，二叉树 [1,2,2,3,4,4,3] 是对称的。

    1

   / \

  2   2

 / \ / \

3  4 4  3
但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:

    1

   / \

  2   2

   \   \

   3    3

 

示例 1：

输入：root = [1,2,2,3,4,4,3]
输出：true
示例 2：

输入：root = [1,2,2,null,3,null,3]
输出：false
 

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
    // 判断A B是否互为镜像
    bool help(TreeNode* A, TreeNode* B) {
        if(A == nullptr && B == nullptr) {
            return true;
        }

        if(A == nullptr || B == nullptr) {
            return false;
        }

        if(A->val != B->val) {
            return false;
        }

        return help(A->left, B->right) && help(A->right, B->left);
    }

    bool isSymmetric(TreeNode* root) {
        if(root == nullptr || (root->left == nullptr && root->right == nullptr)) {
            return true;
        }

        return help(root->left, root->right);
    }
};
