/*
 * @lc app=leetcode.cn id=103 lang=cpp
 *
 * [103] 二叉树的锯齿形层次遍历
 *
 * https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/description/
 *
 * algorithms
 * Medium (54.08%)
 * Likes:    187
 * Dislikes: 0
 * Total Accepted:    47.2K
 * Total Submissions: 86.8K
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * 给定一个二叉树，返回其节点值的锯齿形层次遍历。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。
 * 
 * 例如：
 * 给定二叉树 [3,9,20,null,null,15,7],
 * 
 * ⁠   3
 * ⁠  / \
 * ⁠ 9  20
 * ⁠   /  \
 * ⁠  15   7
 * 
 * 
 * 返回锯齿形层次遍历如下：
 * 
 * [
 * ⁠ [3],
 * ⁠ [20,9],
 * ⁠ [15,7]
 * ]
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
 */
class Solution
{
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {

        vector<vector<int>> ret;

        dfs(root, 0, ret); //递归遍历
        for (int i = 1; i < ret.size(); i += 2)
        {
            std::reverse(ret[i].begin(), ret[i].end()); //间隔翻转
        }
        return ret;
    }

    void dfs(TreeNode *root, int level, vector<vector<int>> &data)
    {
        if (root == NULL)
        {
            return; //循环退出条件
        }

        //每层开始位置（只从左面|右面）
        if (level == data.size())
        {
            vector<int> temp;
            data.push_back(temp);
            //vecotr std::vector::operator[],std::vector::at() 用法一样，
            //if the requested position is out of range by throwing an out_of_range exception.
            //
            //map 不一样，不写代码不知道呀，你真xxx。vecotr 数组，固定位置无法扩容。
            //std::map::operator[]
            //If k does not match the key of any element in the container, 
            //the function inserts a new element with that key and returns a reference to its mapped valu
        }

        data[level].push_back(root->val);

        dfs(root->left, level + 1, data);  //循环变化条件
        dfs(root->right, level + 1, data); //循环变化条件
    }
};
// @lc code=end
