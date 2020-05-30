/*
 * @lc app=leetcode.cn id=121 lang=cpp
 *
 * [121] 买卖股票的最佳时机
 *
 * https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/description/
 *
 * algorithms
 * Easy (53.82%)
 * Likes:    973
 * Dislikes: 0
 * Total Accepted:    209.5K
 * Total Submissions: 387.6K
 * Testcase Example:  '[7,1,5,3,6,4]'
 *
 * 给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
 * 
 * 如果你最多只允许完成一笔交易（即买入和卖出一支股票一次），设计一个算法来计算你所能获取的最大利润。
 * 
 * 注意：你不能在买入股票前卖出股票。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 输入: [7,1,5,3,6,4]
 * 输出: 5
 * 解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
 * ⁠    注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。
 * 
 * 
 * 示例 2:
 * 
 * 输入: [7,6,4,3,1]
 * 输出: 0
 * 解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
 * 
 *  
 * 我第一个感觉 太难了，寻找最低一个，最高的第一个，保证最低在前面。这个怎么办呢？我其实是没有答案的。
 * 还有区分的。最笨方法是什么
 *  [0..i,, n-1] 选择i，从[i+1,n-1] 选择最小一个。
 * 
 * ||  假如i是自高价格，从0到i-1，中选择最小的一个
 */

// @lc code=start
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        if (n == 0)
        {
            return 0;
        }
        
        int profit = 0;

        int low = prices[0];

        for (int i = 1; i < n; i++)
        {
            //假设当前节点i是最价格最高的点
            if (prices[i] > low)
            {

                profit = max(profit, prices[i] - low);
            }
            else
            {
                //low 为历史最低点, 可能是i，也可能是（0-i）位置。
                low = prices[i]; // 受益为负数，不比较
            }
        }

        return profit;
    }
};
// @lc code=end
