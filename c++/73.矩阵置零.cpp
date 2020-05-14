/*
 * @lc app=leetcode.cn id=73 lang=cpp
 *
 * [73] 矩阵置零
 *
 * https://leetcode-cn.com/problems/set-matrix-zeroes/description/
 *
 * algorithms
 * Medium (55.12%)
 * Likes:    217
 * Dislikes: 0
 * Total Accepted:    37.7K
 * Total Submissions: 68.1K
 * Testcase Example:  '[[1,1,1],[1,0,1],[1,1,1]]'
 *
 * 给定一个 m x n 的矩阵，如果一个元素为 0，则将其所在行和列的所有元素都设为 0。请使用原地算法。
 * 
 * 示例 1:
 * 
 * 输入: 
 * [
 * [1,1,1],
 * [1,0,1],
 * [1,1,1]
 * ]
 * 输出: 
 * [
 * [1,0,1],
 * [0,0,0],
 * [1,0,1]
 * ]
 * 
 * 
 * 示例 2:
 * 
 * 输入: 
 * [
 * [0,1,2,0],
 * [3,4,5,2],
 * [1,3,1,5]
 * ]
 * 输出: 
 * [
 * [0,0,0,0],
 * [0,4,5,0],
 * [0,3,1,0]
 * ]
 * 
 * 进阶:
 * 
 * 
 * 一个直接的解决方案是使用  O(mn) 的额外空间，但这并不是一个好的解决方案。
 * 一个简单的改进方案是使用 O(m + n) 的额外空间，但这仍然不是最好的解决方案。
 * 你能想出一个常数空间的解决方案吗？
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if(matrix.size()==0)
            return;
        int row = matrix.size();
        int column = matrix[0].size();
        int index;
        bool status= false;
        for(int i=0;i<row;i++)//扫描出第一个不为零的数，并找出需要清零的列
            for(int j=0;j<column;j++)
            {
                if(matrix[i][j]==0&&!status)
                    index = i,status=true;
                if(matrix[i][j]==0)
                    matrix[index][j]=0;
            }
        if(!status) //没有0
            return;
        for(int i=index+1;i<row;i++)//将行清零
            for(int j=0;j<column;j++)
            {
                if(matrix[i][j]==0)
                {
                    matrix[i].assign(column,0);  
                    break;
                }     
            }

         for(int j=0;j<column;j++) 
            {
                if(matrix[index][j]==0)//该列清零
                {
                    for(int i=0;i<row;i++)
                        matrix[i][j]=0;
                }
            }   

         matrix[index].assign(column,0);
    }

    
};
// @lc code=end

