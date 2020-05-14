/*
 * @lc app=leetcode.cn id=48 lang=cpp
 *
 * [48] 旋转图像
 *
 * https://leetcode-cn.com/problems/rotate-image/description/
 *
 * algorithms
 * Medium (67.67%)
 * Likes:    426
 * Dislikes: 0
 * Total Accepted:    69K
 * Total Submissions: 101.6K
 * Testcase Example:  '[[1,2,3],[4,5,6],[7,8,9]]'
 *
 * 给定一个 n × n 的二维矩阵表示一个图像。
 * 
 * 将图像顺时针旋转 90 度。
 * 
 * 说明：
 * 
 * 你必须在原地旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要使用另一个矩阵来旋转图像。
 * 
 * 示例 1:
 * 
 * 给定 matrix = 
 * [
 * ⁠ [1,2,3],
 * ⁠ [4,5,6],
 * ⁠ [7,8,9]
 * ], 
 *  1   （0,0）---->(0,2)
 *   
 *  2    (0,1) --->(1,2)
 *  
 *  3    (0,2)---->(2,2）
 * 
 *       (i,j) ---->(j,n-i-1)
 *  验证
 *  5   (1,1) ---->（1,1）
 *  6   (1,2) --->(2,1) 
 *  验证正确
 * 
 * 原地旋转输入矩阵，使其变为:
 * [
 * ⁠ [7,4,1],
 * ⁠ [8,5,2],
 * ⁠ [9,6,3]
 * ]
 * 
 * 
 * 示例 2:
 * 
 * 给定 matrix =
 * [
 * ⁠ [ 5, 1, 9,11],
 * ⁠ [ 2, 4, 8,10],
 * ⁠ [13, 3, 6, 7],
 * ⁠ [15,14,12,16]
 * ], 
 * 
 * 原地旋转输入矩阵，使其变为:
 * [
 * ⁠ [15,13, 2, 5],
 * ⁠ [14, 3, 4, 1],
 * ⁠ [12, 6, 8, 9],
 * ⁠ [16, 7,10,11]
 * ]
 * 
 * //看到这个题目我感觉紧张，虽然每个字，认识，感觉常规的算法题目，但是我code出来吗？
 * // 表示很担心，和交流。
 * // 我思路扩展的你做过的类似的题目
 * //swap a b 借助第三个，矩阵也是如此吧。
 * 
 * 如果不借助第三方空间，直接替换，造成数据混乱。 a=b，b=a 结果变得不正确了。怎宝宝
 */

// @lc code=start
class Solution
{
public:
    //直接法，不考虑时间复杂度 O(N2) 空间复杂度 O(N 2)
    void rotate(vector<vector<int>> &matrix)
    {

        // 将图像顺时针旋转 90 度。
        // 根据规律，需要借助额外空间来实现
        int rows = matrix.size();
        if (0 == rows)
        {
            return;
        }
        int cols = matrix[0].size();

        vector<vector<int>> dp(rows, vector<int>(cols,0));

         //copy
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                dp[i][j] = matrix[i][j];
            }
        }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                matrix[j][rows-i - 1] = dp[i][j]; //观察出来的规律
            }
        }

       
    }
};
// @lc code=end
