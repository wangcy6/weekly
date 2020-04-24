/*
 * @lc app=leetcode.cn id=226 lang=cpp
 *
 * [226] 翻转二叉树
 *
 * https://leetcode-cn.com/problems/invert-binary-tree/description/
 *
 * algorithms
 * Easy (74.67%)
 * Likes:    411
 * Dislikes: 0
 * Total Accepted:    70.9K
 * Total Submissions: 94.8K
 * Testcase Example:  '[4,2,7,1,3,6,9]'
 *
 * 翻转一棵二叉树。
 * 
 * 示例：
 * 
 * 输入：
 * 
 * ⁠    4
 * ⁠  /   \
 * ⁠ 2     7
 * ⁠/ \   / \
 * 1   3 6   9
 * 
 * 输出：
 * 
 * ⁠    4
 * ⁠  /   \
 * ⁠ 7     2
 * ⁠/ \   / \
 * 9   6 3   1
 * 
 * 备注:
 * 这个问题是受到 Max Howell 的 原问题 启发的 ：
 * 
 * 谷歌：我们90％的工程师使用您编写的软件(Homebrew)，但是您却无法在面试时在白板上写出翻转二叉树这道题，这太糟糕了。
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
 */
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {

     if( NULL ==root) return root;    
  
    queue<TreeNode*> data;
    data.push(root); 
    
    while(!data.empty())
    {   //出队列
        TreeNode* pcur =data.front();
        data.pop();
        
        //翻转要点
        //1 root保持不变
        //2. 左右2个节点交换的不是数值，是地址，swap需要额外空间 
        // 3. 递归翻转(上层swap之后，讲整个treeswap，移动是指针)
        TreeNode* ptemp =pcur->left;
        pcur->left =pcur->right;
        pcur->right =ptemp;
      

        
        //入队列
        if(pcur->left)
        {
          data.push(pcur->left);
        }

         if(pcur->right)
        {
          data.push(pcur->right);
        }

    }

    return root;
    }
};
// @lc code=end

