/*
 * @lc app=leetcode.cn id=85 lang=cpp
 *
 * [85] 最大矩形
 *
 * https://leetcode-cn.com/problems/maximal-rectangle/description/
 *
 * algorithms
 * Hard (45.26%)
 * Likes:    415
 * Dislikes: 0
 * Total Accepted:    27.4K
 * Total Submissions: 59.6K
 * Testcase Example:  '[["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]'
 *
 * 给定一个仅包含 0 和 1 的二维二进制矩阵，找出只包含 1 的最大矩形，并返回其面积。
 * 
 * 示例:
 * 
 * 输入:
 * [
 * ⁠ ["1","0","1","0","0"],
 * ⁠ ["1","0","1","1","1"],
 * ⁠ ["1","1","1","1","1"],
 * ⁠ ["1","0","0","1","0"]
 * ]
 * 输出: 6
 * 
 */

// @lc code=start
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int i,j,k;
        int res=0;
        heights.push_back(0);
        stack<int>s; s.push(-1);
        for(i=0;i<heights.size();i++){
            if(i==0||s.size()==1||heights[i]>=heights[s.top()]) s.push(i);
            while(s.size()>1&&heights[i]<heights[s.top()]){
                k=s.top();s.pop();res=max((i-s.top()-1)*heights[k],res);
            }
            s.push(i);
        }
        return res;      
    }
    int maximalRectangle(vector<vector<char>>& matrix) {
        int i,j;
        int m=matrix.size();
        if(m==0) return 0;
        int n=matrix[0].size();
        vector<int>v(n);
        int k=0;
        for(i=0;i<m;i++){
            for(j=0;j<n;j++)
              v[j]=matrix[i][j]=='1'?v[j]+1:0;
            k=max(k,largestRectangleArea(v));
        }
        
        return k;
    }
};

// @lc code=end

