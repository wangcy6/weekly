/*
 * @lc app=leetcode.cn id=106 lang=cpp
 *
 * [106] 从中序与后序遍历序列构造二叉树
 *
 * https://leetcode-cn.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/description/
 *
 * algorithms
 * Medium (67.69%)
 * Likes:    195
 * Dislikes: 0
 * Total Accepted:    34.7K
 * Total Submissions: 50.8K
 * Testcase Example:  '[9,3,15,20,7]\n[9,15,7,20,3]'
 *
 * 根据一棵树的中序遍历与后序遍历构造二叉树。
 * 
 * 注意:
 * 你可以假设树中没有重复的元素。
 * 
 * 例如，给出
 * 
 * 中序遍历 inorder = [9,3,15,20,7]
 * 后序遍历 postorder = [9,15,7,20,3]
 * 
 * 返回如下的二叉树：
 * 
 * ⁠   3
 * ⁠  / \
 * ⁠ 9  20
 * ⁠   /  \
 * ⁠  15   7
 * 
 * 
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 * //如何从线性到二叉树 我想到的是折半查找的例子。
 * //流程绘制不出来呢？
 * // 别人都说分治法思想 我不明白呢
 * //https://leetcode-cn.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/solution/si-lu-qing-xi-dai-ma-jian-ji-he-105ti-si-lu-yi-zhi/
 * //https://leetcode-cn.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/solution/cong-zhong-xu-yu-hou-xu-bian-li-xu-lie-gou-zao-e-5/
 */

class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int pos = inorder.size()-1;
        return buildTree(postorder, pos, inorder, 0, inorder.size() - 1);
    }

    TreeNode* buildTree(vector<int>& postorder, int& pos, vector<int>& inorder, int left, int right) {
        if (pos < 0 || left > right) return 0;
        int p = left;
        while (p <= right && postorder[pos] != inorder[p]) p ++;
        TreeNode* node = new TreeNode(postorder[pos]);
        if (p+1 <= right) node->right = buildTree(postorder, --pos, inorder, p+1, right);
        if (left <= p-1) node->left = buildTree(postorder, --pos, inorder, left, p-1);
        return node;
    }
};

// class Solution1
// {
// public:
//     /**
//      * 1. 方法 分治,数组[left,right]就是边界
//      * 2. 算法
//      * 3. 实现
//      */
//     TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
//     {

//         //假如数据输入合法
//         //
//         return buildTree(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
//     }

//     TreeNode *buildTree(vector<int> &inorder, int left1, int right1, vector<int> &postorder, int left2, int right2)
//     {

//         // 每次取postorder的最后一个值mid，将其作为树的根节点
//         // 然后从inroder中找到mid，将其分割成为两部分，左边作为mid的左子树，右边作为mid的右子树
//         // Inorder   [3 4 6] 8 [9 10 11]
//         // postorder [3 6 4]   [9 11 10] 8
//         // tree:     8 4 10 3 6 9 11
//         if (left1 >right1 || left2 >right2)
//         { 
//             return NULL;//递归退出条件,如果只有0个元素 一个不合法数组，返回NULl 
//         } 

//         if (left1 == right1 || left2 == right2)
//         { 
//             return new TreeNode(inorder[left1]);//递归退出条件,如果只有1个元素
//         } 

//         //01一棵树的root节点就是postorder最后一个节点。
//         int rootVal =postorder[right2];

//         //02 寻找到root节点，从inorder，判断left tree 元素范围.和右子tree的范围。
//         int dividePoint = 0;
//         for (int i = left1; i <= right1; i++) {
//             if (inorder[i] == rootVal) {
//                 dividePoint = i;
//                 break;
//             }
//         }

//         //03 新建这个节点
//         TreeNode *root = new TreeNode(rootVal);


//        root->left=buildTree(inorder, left1,dividePoint-1, postorder, left2, right2);
//        root->right=buildTree(inorder, dividePoint+1, right1, postorder, left2, right2);

//        return root;

//     }
// };

// @lc code=end
