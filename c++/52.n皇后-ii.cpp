/*
 * @lc app=leetcode.cn id=52 lang=cpp
 *
 * [52] N皇后 II
 *
 * https://leetcode-cn.com/problems/n-queens-ii/description/
 *
 * algorithms
 * Hard (77.84%)
 * Likes:    114
 * Dislikes: 0
 * Total Accepted:    21.6K
 * Total Submissions: 27.6K
 * Testcase Example:  '4'
 *
 * n 皇后问题研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
 * 
 * 
 * 
 * 上图为 8 皇后问题的一种解法。
 * 
 * 给定一个整数 n，返回 n 皇后不同的解决方案的数量。
 * 
 * 示例:
 * 
 * 输入: 4
 * 输出: 2
 * 解释: 4 皇后问题存在如下两个不同的解法。
 * [
 * [".Q..",  // 解法 1
 * "...Q",
 * "Q...",
 * "..Q."],
 * 
 * ["..Q.",  // 解法 2
 * "Q...",
 * "...Q",
 * ".Q.."]
 * ]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 
 * 皇后，是国际象棋中的棋子，意味着国王的妻子。皇后只做一件事，那就是“吃子”。当她遇见可以吃的棋子时，就迅速冲上去吃掉棋子。当然，她横、竖、斜都可走一或七步，可进可退。（引用自
 * 百度百科 - 皇后 ）
 * 
 * 
 */

// @lc code=start
class Solution {
public:
  //拒绝奇技淫巧,从简单开始。

   int dfs(int now, int n, vector<int> &path, vector<bool> &sum, vector<bool> &diff){
        if(now == n) return 1;
        int res = 0;
        for(int i = now; i < n; i++) {
            swap(path[i], path[now]);   //循环一轮后面不同的值
            if(sum[now + path[now]] && diff[now + n - path[now]]) {//与前面的皇后无冲突
                sum[now + path[now]] = 0;
                diff[now + n - path[now]] = 0;
                res += dfs(now + 1, n, path, sum, diff); //下一个数
                sum[now + path[now]] = 1;   //回溯回复状态
                diff[now + n - path[now]] = 1;  //恢复状态
            }
            swap(path[i], path[now]);   //回溯
        }
        return res;
    }
    int totalNQueens(int n) {
        vector<int> path(n, 0);
        vector<bool> sum(2*n, 1), diff(2*n, 1); //行与列的和及差，判断是否冲突用
        for(int i = 0; i < n; i++)  path[i] = i;
        return dfs(0, n, path, sum, diff);
    }
};
// @lc code=end

