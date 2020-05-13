/*
 * @lc app=leetcode.cn id=98 lang=cpp
 *
 * [98] 验证二叉搜索树
 *
 * https://leetcode-cn.com/problems/validate-binary-search-tree/description/
 *
 * algorithms
 * Medium (29.67%)
 * Likes:    575
 * Dislikes: 0
 * Total Accepted:    117.6K
 * Total Submissions: 377.8K
 * Testcase Example:  '[2,1,3]'
 *
 * 给定一个二叉树，判断其是否是一个有效的二叉搜索树。
 * 
 * 假设一个二叉搜索树具有如下特征：
 * 
 * 
 * 节点的左子树只包含小于当前节点的数。
 * 节点的右子树只包含大于当前节点的数。
 * 所有左子树和右子树自身必须也是二叉搜索树。
 * 
 * 
 * 示例 1:
 * 
 * 输入:
 * ⁠   2
 * ⁠  / \
 * ⁠ 1   3
 * 输出: true
 * 
 * 
 * 示例 2:
 * 
 * 输入:
 * ⁠   5
 * ⁠  / \
 * ⁠ 1   4
 * / \
 * 3   6
 * 输出: false
 * 解释: 输入为: [5,1,4,null,null,3,6]。
 * 根节点的值为 5 ，但是其右子节点值为 4 。
 * 
 * 1 为什么不能直接通过 root 判断左右，因为定义理解错误
 * 2 如何定义上一个节点。
 * 3 知觉全部遍历 需要消耗更多时间
 * 4 如何记录上一个数值呢
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
    //非递归
    //利用栈实现中序遍历,依然需要一个pre 指针保存出栈的上一个记录
    //24 ms
    bool isValidBST(TreeNode *root)
    {
        if (NULL == root)
            return true;
        stack<TreeNode *> path; //记录左右子树访问顺序
        TreeNode *pre = NULL;   //当前节点前一个node

        //path.push(root); //默认有一个记录，会造成root元素重复插入。

        while (path.empty() == false || root != NULL)
        {
            //如果节点存在，就入栈 ,if 判断非常重要，这样左节点一直入栈操作。直到为null。
            if (root)
            {
                path.push(root);
                root = root->left;
            }
            else
            {
                TreeNode *ptemp = path.top();
                path.pop();

                //业务逻辑判断，
                if (pre && pre->val >= ptemp->val)
                {
                    return false;
                }

                pre = ptemp;
                //下一个元素
                root = ptemp->right;
            }
        }

        return true;
    }
    bool isValidBST1(TreeNode *root)
    {
        TreeNode *pre = NULL; //这个结构很重要，比较大小，肯定需要2个元素。
        //引用 避免对root节点内容，进行赋值操作。

        //return isValidBST(root, &pre);有在这里语法错误了
        return isValidBST1(root, pre);
    }

    bool isValidBST1(TreeNode *root, TreeNode *&pre)
    {
        if (NULL == root)
            return true;
        //为什么null节点，一定是二叉搜索树。因为假如返回false，一个合法的tree最终结果返回false

        // isValidBST(root->left, pre); 这样写不符合定义，只要有一个错误，后面不需要遍历了。
        if (false == isValidBST1(root->left, pre))
        {
            return false;
        }

        //中顺遍历第一个节点是没有前序的,pre = NULL ,这个不需要比较
        //判断是否升序。
        if (pre != NULL && pre->val >= root->val)
        {
            return false;
        }

        //最重要的pre根本没有发生变动忘记了。
        //sb了 赋值，不是判断相等
        // pre ==root;
        pre = root;

        if (false == isValidBST1(root->right, pre))
        {
            return false;
        }

        return true; //root节点左右子tree都符合要求。
    }
};
// @lc code=end
