/*
 * @lc app=leetcode.cn id=84 lang=cpp
 *
 * [84] 柱状图中最大的矩形
 *
 * https://leetcode-cn.com/problems/largest-rectangle-in-histogram/description/
 *
 * algorithms
 * Hard (39.27%)
 * Likes:    582
 * Dislikes: 0
 * Total Accepted:    46.1K
 * Total Submissions: 116.8K
 * Testcase Example:  '[2,1,5,6,2,3]'
 *
 * 给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
 * 
 * 求在该柱状图中，能够勾勒出来的矩形的最大面积。
 * 
 * 
 * 
 * 
 * 
 * 以上是柱状图的示例，其中每个柱子的宽度为 1，给定的高度为 [2,1,5,6,2,3]。
 * 
 * 
 * 
 * 
 * 
 * 图中阴影部分为所能勾勒出的最大矩形面积，其面积为 10 个单位。
 * 
 * 
 * 
 * 示例:
 * 
 * 输入: [2,1,5,6,2,3]
 * 输出: 10
 * 
 */

// @lc code=start
class Solution {
public:
    int largestRectangleArea(vector<int> &heights)
    {
        stack<int> st;
        heights.push_back(0); //结尾虚拟柱子高度0
        int size = heights.size();
        int res = 0;
        for (int i = 0; i < size; ++i)
        {
            while (!st.empty() && heights[st.top()] >= heights[i])
            {
                int val = st.top();
                st.pop();
                res = max(res, heights[val] * (st.empty() ? i : (i - st.top() - 1))); //宽度不包含当前元素
            }
            st.push(i);
        }
        return res;
    }
};
// @lc code=end

