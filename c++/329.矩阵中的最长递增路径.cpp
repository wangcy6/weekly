/*
 * @lc app=leetcode.cn id=329 lang=cpp
 *
 * [329] 矩阵中的最长递增路径
 *
 * https://leetcode-cn.com/problems/longest-increasing-path-in-a-matrix/description/
 *
 * algorithms
 * Hard (40.14%)
 * Likes:    157
 * Dislikes: 0
 * Total Accepted:    12.5K
 * Total Submissions: 31K
 * Testcase Example:  '[[9,9,4],[6,6,8],[2,1,1]]'
 *
 * 给定一个整数矩阵，找出最长递增路径的长度。
 * 
 * 对于每个单元格，你可以往上，下，左，右四个方向移动。 你不能在对角线方向上移动或移动到边界外（即不允许环绕）。
 * 
 * 示例 1:
 * 
 * 输入: nums = 
 * [
 * ⁠ [9,9,4],
 * ⁠ [6,6,8],
 * ⁠ [2,1,1]
 * ] 
 * 输出: 4 
 * 解释: 最长递增路径为 [1, 2, 6, 9]。
 * 
 * 示例 2:
 * 
 * 输入: nums = 
 * [
 * ⁠ [3,4,5],
 * ⁠ [3,2,6],
 * ⁠ [2,2,1]
 * ] 
 * 输出: 4 
 * 解释: 最长递增路径是 [3, 4, 5, 6]。注意不允许在对角线方向上移动。
 * 
 * 
 */

// @lc code=start
class Solution
{
public:
    int longestIncreasingPath(vector<vector<int>> &matrix)
    {

        //在二维矩阵中，每一个点可能成为最长路径开始节点，其他任意节点成为最长路径结束节点。
        //类比tree的高度,从上到下依赖路径。
        //最长递增路径的长度.思路：记录每个(i,j) 终点位置路径。然后判断最长的。

        int rows = matrix.size();
        if (0 == rows)
        {
            return 0;
        }
        int cols = matrix[0].size();

        vector<vector<int>> dp(rows, vector<int>(cols, 1));

        int path = 0;
        int temp =0;

        //二维数组遍历
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {    
             
                 temp = dfs(matrix, i, j, INT_MIN, dp); //root节点上面一个节点，设定为最小值
                
                path=max(temp,path);
            }
        }

        return path;
    }

    int dfs(vector<vector<int>> &matrix, int i, int j, int lastNode, vector<vector<int>> &dp)
    {
        //范围判断
        if( i<0 || j<0 || i>=matrix.size() || j>= matrix[0].size())
        {
            return 0;
        }

         //如果不是递增，之间为1.
         //就无法利用下一个节点。
         // [3, 4, 5, 6] 6  叶子节点。
        if (lastNode >=matrix[i][j])
        { 
            return 0;
        }

        if (dp[i][j] > 1)
        {
            return dp[i][j];
        }
       

         //依赖关系：这个不是从上到下或者从下到上关系。每个节点都为其他人服务
        int left  =dfs(matrix,i,j-1,matrix[i][j],dp);
        int right =dfs(matrix,i,j+1,matrix[i][j],dp);
        int up    =dfs(matrix,i+1,j,matrix[i][j],dp);
        int down  =dfs(matrix,i-1,j,matrix[i][j],dp);
      
      dp[i][j]=max(max(left,right),max(up,down))+1;

      return dp[i][j];
    }
};
// @lc code=end
