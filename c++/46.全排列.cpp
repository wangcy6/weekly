/*
 * @lc app=leetcode.cn id=46 lang=cpp
 *
 * [46] 全排列
 *
 * https://leetcode-cn.com/problems/permutations/description/
 *
 * algorithms
 * Medium (74.67%)
 * Likes:    673
 * Dislikes: 0
 * Total Accepted:    120.5K
 * Total Submissions: 158.7K
 * Testcase Example:  '[1,2,3]'
 *
 * 给定一个 没有重复 数字的序列，返回其所有可能的全排列。
 * 
 * 示例:
 * 
 * 输入: [1,2,3]
 * 输出:
 * [
 * ⁠ [1,2,3],
 * ⁠ [1,3,2],
 * ⁠ [2,1,3],
 * ⁠ [2,3,1],
 * ⁠ [3,1,2],
 * ⁠ [3,2,1]
 * ]
 * 
 */

// @lc code=start
class Solution
{
public:
    vector<vector<int> > permute(vector<int> &nums)
    {

        vector<vector<int>> ret;               //返回其所有可能的全排列
        vector<int> path;                      //用栈记录元素路径。
        vector<bool> used(nums.size(), false); //是否被标记过。
        dfs(nums,0,path,used,ret);
        return ret;
    }

    void dfs(vector<int> &nums, int start, vector<int> &path, vector<bool> &used, vector<vector<int>> &ret)
    {
        //root to leaf ,leaf node is null
        if (start == nums.size())
        {
            ret.push_back(path); //递归退出条件
        }

        //每次都有n-i个选择,一个深度3的三叉树
       for(int i=0;i<nums.size();i++)
       {
          //当前分支，如果以前使用过，这次不选择了
          if(used[i] ==true)
          {
              continue;
          }

          used[i] =true;
          path.push_back(nums[i]);//入栈

         dfs(nums,start+1,path,used,ret);
         used[i] =false;
         path.pop_back();//出栈，返回,

       }   

    }
};
// @lc code=end
