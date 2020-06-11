/*
 * @lc app=leetcode.cn id=378 lang=cpp
 *
 * [378] 有序矩阵中第K小的元素
 *
 * https://leetcode-cn.com/problems/kth-smallest-element-in-a-sorted-matrix/description/
 *
 * algorithms
 * Medium (58.77%)
 * Likes:    232
 * Dislikes: 0
 * Total Accepted:    21.9K
 * Total Submissions: 36.8K
 * Testcase Example:  '[[1,5,9],[10,11,13],[12,13,15]]\n8'
 *
 * 给定一个 n x n 矩阵，其中每行和每列元素均按升序排序，找到矩阵中第k小的元素。
 * 请注意，它是排序后的第 k 小元素，而不是第 k 个不同的元素。
 * 
 * 
 * 
 * 示例:
 * 
 * matrix = [
 * ⁠  [ 1,  5,  9],
 * ⁠  [10, 11, 13],
 * ⁠  [12, 13, 15]
 * ],
 * k = 8,
 * 
 * 1 5 9 10 11 12 13 13 15
 * 返回 13。
 * 
 *  Solution 1  priority queue
 *  从哪里开始下手，
 *   我观察不出来 有序数组 之间的关系，有什么规律，看了多次，也想不出来，不能这样干耗着，放弃巧妙的算法。
 *   make it work
 *   分析题目 第 k 小元素，假如排序后结果
 *  1 5 9 10 11 | k | 12 13 13 15 
 *  K之后元素统统不要，建立大小为k的优先级队列。
 *  时间复杂度为O(n^2 log(k)) 空间复杂度为O(k)。
 * 提示：
 * 你可以假设 k 的值永远是有效的, 1 ≤ k ≤ n^2 。
 *  
 */

// @lc code=start
class Solution
{
public:
     //164 ms---13.4 MB 
     //1 ≤ k ≤ n^2
    int kthSmallest(vector<vector<int>> &matrix, int k)
    {
        priority_queue<int> bigHeap; //第 k 小元素，就是k个元素中最大的那个。
        int m = matrix.size();
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m; j++)
            {
                bigHeap.push(matrix[i][j]);
                // 忘记放到{}里面，每次插入一次，就要判断一次
                //必须全部遍历。
                if (bigHeap.size() > k)
                {
                    bigHeap.pop();
                }
            }
        }

        return bigHeap.top(); //直接获取结果
    }
};
// @lc code=end
