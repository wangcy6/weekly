/*
 * @lc app=leetcode.cn id=87 lang=cpp
 *
 * [87] 扰乱字符串
 *
 * https://leetcode-cn.com/problems/scramble-string/description/
 *
 * algorithms
 * Hard (46.06%)
 * Likes:    121
 * Dislikes: 0
 * Total Accepted:    9.6K
 * Total Submissions: 20.7K
 * Testcase Example:  '"great"\n"rgeat"'
 *
 * 给定一个字符串 s1，我们可以把它递归地分割成两个非空子字符串，从而将其表示为二叉树。
 * 
 * 下图是字符串 s1 = "great" 的一种可能的表示形式。
 * 
 * ⁠   great
 * ⁠  /    \
 * ⁠ gr    eat
 * ⁠/ \    /  \
 * g   r  e   at
 * ⁠          / \
 * ⁠         a   t
 * 
 * 
 * 在扰乱这个字符串的过程中，我们可以挑选任何一个非叶节点，然后交换它的两个子节点。
 * 
 * 例如，如果我们挑选非叶节点 "gr" ，交换它的两个子节点，将会产生扰乱字符串 "rgeat" 。
 * 
 * ⁠   rgeat
 * ⁠  /    \
 * ⁠ rg    eat
 * ⁠/ \    /  \
 * r   g  e   at
 * ⁠          / \
 * ⁠         a   t
 * 
 * 
 * 我们将 "rgeat” 称作 "great" 的一个扰乱字符串。
 * 
 * 同样地，如果我们继续交换节点 "eat" 和 "at" 的子节点，将会产生另一个新的扰乱字符串 "rgtae" 。
 * 
 * ⁠   rgtae
 * ⁠  /    \
 * ⁠ rg    tae
 * ⁠/ \    /  \
 * r   g  ta  e
 * ⁠      / \
 * ⁠     t   a
 * 
 * 
 * 我们将 "rgtae” 称作 "great" 的一个扰乱字符串。
 * 
 * 给出两个长度相等的字符串 s1 和 s2，判断 s2 是否是 s1 的扰乱字符串。
 * 
 * 示例 1:
 * 
 * 输入: s1 = "great", s2 = "rgeat"
 * 输出: true
 * 
 * 
 * 示例 2:
 * 
 * 输入: s1 = "abcde", s2 = "caebd"
 * 输出: false
 * 
 */

// @lc code=start
class Solution {
public:
    bool isScramble(string s1, string s2) {
        if (s1.size() != s2.size()) return false;
        if (s1.empty()) return true;
        int N = s1.size();
        vector<vector<vector<bool> > > dp(N + 1, vector<vector<bool> >(N, vector<bool>(N, false)));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                dp[1][i][j] = s1[i] == s2[j];
            }
        }
        for (int len = 2; len <= N; ++len) {
            for (int i = 0; i < N && i + len - 1 < N; ++i) {
                for (int j = 0; j < N && j + len - 1 < N; ++j) {
                    for (int k = 1; k < len; ++k) {
                        if (dp[k][i][j] && dp[len - k][i + k][j + k]) {
                            dp[len][i][j] = true;
                            break;
                        }
                        if (dp[k][i][j + len - k] && dp[len - k][i + k][j]) {
                            dp[len][i][j] = true;
                            break;
                        }
                    }
                }
            }
        }
        return dp[N][0][0];
    }
};


// @lc code=end

