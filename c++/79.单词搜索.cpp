/*
 * @lc app=leetcode.cn id=79 lang=cpp
 *
 * [79] 单词搜索
 *
 * https://leetcode-cn.com/problems/word-search/description/
 *
 * algorithms
 * Medium (41.10%)
 * Likes:    401
 * Dislikes: 0
 * Total Accepted:    55.8K
 * Total Submissions: 134.8K
 * Testcase Example:  '[["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]]\n"ABCCED"'
 *
 * 给定一个二维网格和一个单词，找出该单词是否存在于网格中。
 * 
 * 单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
 * 
 * 
 * 
 * 示例:
 * 
 * board =
 * [
 * ⁠ ['A','B','C','E'],
 * ⁠ ['S','F','C','S'],
 * ⁠ ['A','D','E','E']
 * ]
 * 
 * 给定 word = "ABCCED", 返回 true
 * 给定 word = "SEE", 返回 true
 * 给定 word = "ABCB", 返回 false
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * board 和 word 中只包含大写和小写英文字母。
 * 1 <= board.length <= 200
 * 1 <= board[i].length <= 200
 * 1 <= word.length <= 10^3
 *  https://leetcode-cn.com/problems/word-search/solution/tu-jie-di-gui-shen-du-you-xian-sou-suo-by-z1m/
 * 
 *  从 (i, j) 出发，朝它的上下左右试探，看看它周边的这四个元素是否能匹配 word 的下一个字母
*   如果匹配到了：带着该元素继续进入下一个递归
*   如果都匹配不到：返回 False
*  当word 的所有字母都完成匹配后，整个流程返回 True
*  
 *   难点：单词任意旋转，游走，我怎么找到相关方向
 *   
 */

// @lc code=start
class Solution
{
public:
    //思路: 矩阵回溯
    //时间复杂度:24 ms
    //思路描述：
    // 1  从board任意一个点开始，采用深度优先搜索 这里无法做到重复利用。
    // 2. 对每个点(i, j)它的上下左右试探 回溯
    //    2.1如果匹配到了：带着该元素继续进入下一个递归能匹配 word 的下一个字母
    //    2.2 如果数据不匹配||越界 || 大于word 直接返回,回溯 处理。
    //    说明：历史元素是否访问过，通过修改自身代替矩阵来标记。visied和通过大小判断的。 A--A (AA)
    //    2.3 当word 的所有字母都完成匹配后，整个流程返回 True
    bool exist(vector<vector<char>> &board, string word)
    {

        //从board任意一个点开始，采用深度优先搜索。
        int row = board.size();

        if (row == 0 || word.size() == 0)
        {
            return false;
        }
        int col = board[0].size();

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                //(i,j) 每个节点都可能成为开始节点。
                if (dfs(i, j, 0, word, board))
                {
                    return true;
                }
            }
        }

        return false; //全部搜索，也没有一个匹配。
    }

    bool dfs(int i, int j, int cur, string &word, vector<vector<char>> &board)
    {

        if (cur == word.size())
        {
            return true; //能走到这里说明 之前都相同,word相当于正确的路径。 //exit
        }
        //如果数据不匹配||越界 || 大于word 直接返回
        if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size() || cur >= word.size() || board[i][j] != word[cur])
        {
            return false;
        } //exit

        //对每个点(i, j)它的上下左右试探 回溯
        char visited = board[i][j];
        board[i][j] = '*'; //防止死循环 A-->B B-->A。*代表其他字符，与word比较必然失败。

        //(变化是坐标))
        bool result = dfs(i, j - 1, cur + 1, word, board) || dfs(i, j + 1, cur + 1, word, board) || dfs(i - 1, j, cur + 1, word, board) || dfs(i + 1, j, cur + 1, word, board);

        board[i][j] = visited; //每层递归递归都有这样一个标记。

        return result;
    }
};
// @lc code=end
