/*
 * @lc app=leetcode.cn id=97 lang=cpp
 *
 * [97] 交错字符串
 *
 * https://leetcode-cn.com/problems/interleaving-string/description/
 *
 * algorithms
 * Hard (39.46%)
 * Likes:    167
 * Dislikes: 0
 * Total Accepted:    13.4K
 * Total Submissions: 33.5K
 * Testcase Example:  '"aabcc"\n"dbbca"\n"aadbbcbcac"'
 *
 * 给定三个字符串 s1, s2, s3, 验证 s3 是否是由 s1 和 s2 交错组成的。
 * 
 * 示例 1:
 * 
 * 输入: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
 * 输出: true
 * 
 * 
 * 示例 2:
 * 
 * 输入: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
 * 输出: false
 * 
 */

// @lc code=start
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n1 = s1.size();
        int n2 = s2.size();
        int n3 = s3.size();
        if(n1 + n2 != n3) {
            return false;
        }
        //dp[i][j] s1的前i个字符和s2的前j个字符是否能交错组成s3的前i+j个字符
        vector<vector<bool>>dp(n1 + 1, vector<bool>(n2 + 1, false));
        dp[0][0] = true;
        //初始化：第一列和第一行代表""，只需判断s1和s2与s3相同的地方即可
        for(int i = 0; i < n1; i++) {
            if(s1[i] == s3[i]) {
                dp[i + 1][0] = true; //注意下标对应关系，dp是从1开始存放字母的
            } else {
                break;
            }
        }
        for(int i = 0; i < n2; i++) {
            if(s2[i] == s3[i]) {
                dp[0][i + 1] = true; //注意下标对应关系，dp是从1开始存放字母的
            } else {
                break;
            }
        }
        //动态方程
        //需要判断三个状态是否为true
        // 1 如果dp[i-1][j-1]为真，说明s3前i+j-2个字符可以由s1的前i-1个和s2的前j-1个字母组成，则需要比较s1的第i个和s2的第j个是否是s3的i+j-1、i+j个字符串（顺序没有关系）
        // 2 如果dp[i][j-1]为真，说明s3前i+j-1个字符可以由s1的前i个和s2的前j-1个字母组成，只需比较s2的第j个字符是否是s3的第i+j个字符即可
        // 3 如果dp[i-1][j]为真，同理，只需比较s1的第i个字符是否是s3的第i+j个字符
        // 注意因为s1、s2是从下标0开始存储，所以要在字符串寻找字符时下标要减1
        for(int i = 1; i <= n1; i++) {
            for(int j = 1; j <= n2; j++) {
                if(dp[i-1][j-1]) {
                    //注意下标转换
                    if(s1[i-1] == s3[i+j-2] && s2[j-1] == s3[i+j-1] 
                    || s1[i-1] == s3[i+j-1] && s2[j-1] == s3[i+j-2]) {
                        dp[i][j] = true;
                        continue;
                    }
                } 
                if(dp[i][j-1]) {
                    if(s2[j-1] == s3[i+j-1]) {
                        dp[i][j] = true;
                        continue;
                    }
                }
                if(dp[i-1][j]) {
                    if(s1[i-1] == s3[i+j-1]) {
                        dp[i][j] = true;
                        continue;
                    }
                }
            }
        }
        return dp[n1][n2];
    }
};

// @lc code=end

