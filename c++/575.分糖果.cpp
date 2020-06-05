/*
 * @lc app=leetcode.cn id=575 lang=cpp
 *
 * [575] 分糖果
 *
 * https://leetcode-cn.com/problems/distribute-candies/description/
 *
 * algorithms
 * Easy (66.18%)
 * Likes:    69
 * Dislikes: 0
 * Total Accepted:    20.6K
 * Total Submissions: 31K
 * Testcase Example:  '[1,1,2,2,3,3]'
 *
 * 
 * 给定一个偶数长度的数组，其中不同的数字代表着不同种类的糖果，每一个数字代表一个糖果。
 * 你需要把这些糖果平均分给一个弟弟和一个妹妹。返回妹妹可以获得的最大糖果的种类数。
 * 
 * 示例 1:
 * 
 * 
 * 输入: candies = [1,1,2,2,3,3]
 * 输出: 3
 * 解析: 一共有三种种类的糖果，每一种都有两个。
 * ⁠    最优分配方案：妹妹获得[1,2,3],弟弟也获得[1,2,3]。这样使妹妹获得糖果的种类数最多。
 * 
 * 
 * 示例 2 :
 * 
 * 
 * 输入: candies = [1,1,2,3]
 * 输出: 2
 * 解析: 妹妹获得糖果[2,3],弟弟获得糖果[1,1]，妹妹有两种不同的糖果，弟弟只有一种。这样使得妹妹可以获得的糖果种类数最多。
 * 
 * 
 * 注意:
 * 
 * 
 * 数组的长度为[2, 10,000]，并且确定为偶数。
 * 数组中数字的大小在范围[-100,000, 100,000]内。
 * 
 * 
 * 
 * 
 *  第一感觉，一个随机的事情，如何判断最后结果呀，就像买彩票一样。需要撞大运，
 *  冷静，冷静 在想想 
 *  如果获得最多，
 *  1 不管糖果，选择怎么分，轮流选择1个，2个 n/2,选择一个最高的的。
 *  2 排序，统计前后个数
 *  这样想法，正确吗,有用吗 我不清楚
 *  
 *  
 *   
 * 
 */

// @lc code=start
class Solution {
public:
    int distributeCandies(vector<int>& candies) {
       
       unordered_set<int> count;

       for(auto temp:candies)
       {
           count.insert(temp);
       }

       return  min(count.size(),candies.size()/2);

    }
};
// @lc code=end

