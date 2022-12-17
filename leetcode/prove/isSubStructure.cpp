/*
输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)

B是A的子结构， 即 A中有出现和B相同的结构和节点值。

例如:
给定的树 A:

     3

    / \

   4   5

  / \

 1   2
给定的树 B：

   4

  /

 1
返回 true，因为 B 与 A 的一个子树拥有相同的结构和节点值。

示例 1：

输入：A = [1,2,3], B = [3,1]
输出：false
示例 2：

输入：A = [3,4,5,1,2], B = [4,1]
输出：true
限制：

0 <= 节点个数 <= 10000
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
    bool help(TreeNode* A, TreeNode* B)
    {
        // B结束了 表示B为A的子节点
        if (B == nullptr) {
            return true;
        }

        // A结束 但B没有 返回false
        if (A == nullptr) {
            return false;
        }

        if (A->val != B->val) {
            return false;
        }

        // 判断AB的左右子节点
        return help(A->left, B->left) && help(A->right, B->right);
    }

    bool isSubStructure(TreeNode* A, TreeNode* B)
    {
        // 空树不为任意树的子节点
        if (B == nullptr || A == nullptr) {
            return false;
        }

        // 判断B是不是A的子结构
        if (help(A, B)) {
            return true;
        }

        // 判断B是不是A子节点的子结构
        return isSubStructure(A->left, B) || isSubStructure(A->right, B);
    }
};
