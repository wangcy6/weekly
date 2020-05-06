/*
 * @lc app=leetcode.cn id=77 lang=cpp
 *
 * [77] 组合
 *
 * https://leetcode-cn.com/problems/combinations/description/
 *
 * algorithms
 * Medium (73.41%)
 * Likes:    261
 * Dislikes: 0
 * Total Accepted:    48K
 * Total Submissions: 65.2K
 * Testcase Example:  '4\n2'
 *
 * 给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。
 * 
 * 示例:
 * 
 * 输入: n = 4, k = 2
 * 输出:
 * [
 * ⁠ [2,4],
 * ⁠ [3,4],
 * ⁠ [2,3],
 * ⁠ [1,2],
 * ⁠ [1,3],
 * ⁠ [1,4],
 * ]
 * 
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> list;
        vector<int> result;
        dfs(list,result,n,k,0,-1);       
        return list;
    }
    void dfs(vector<vector<int>>& list, vector<int>& result, int n, int k, int pos,int pre){
        if(pos == k){
            list.push_back(result);
            return;
        }
        if((pos + (n-pre)) <= k)return;//剪枝，添加之后用时节省了2/3
        //在当前对不合理的取值进行判断，结束下一层的递归操作。
        //如果当前剩余可操作数字的个数即（n-pre）< k-pos+1(即组合中有待赋值的位置个数)，（+1是因为当前pos还没有进行操作），则可以判断该条路径不可能得到正确的解，不再向下探寻。
        for(int i=pre+1; i<n ; i++){
            result.push_back(i+1);
            pre = i;
            dfs(list,result,n,k,pos+1,pre);
            result.pop_back();//回溯
        }
        return;
    }
};
// @lc code=end

