/*
 * @lc app=leetcode.cn id=387 lang=cpp
 *
 * [387] 字符串中的第一个唯一字符
 *
 * https://leetcode-cn.com/problems/first-unique-character-in-a-string/description/
 *
 * algorithms
 * Easy (44.27%)
 * Likes:    213
 * Dislikes: 0
 * Total Accepted:    78.9K
 * Total Submissions: 174.6K
 * Testcase Example:  '"leetcode"'
 *
 * 给定一个字符串，找到它的第一个不重复的字符，并返回它的索引。如果不存在，则返回 -1。
 * 
 * 案例:
 * 
 * 
 * s = "leetcode"
 * 返回 0.
 * 
 * s = "loveleetcode",
 * 返回 2.
 * 
 * 
 * 
 * 
 * 注意事项：您可以假定该字符串只包含小写字母。
 * 
 */

// @lc code=start
class Solution {
public:
     /**
      * 1  统计字符出现次数，你马上想到就是key/value，就是散列表。
      *  为什么不是map呢因为我不太清楚，https://www.youtube.com/watch?v=ncHmEUmJZf4 C++性能优化指南.pdf 大约消耗4个小时阅读。
      * 
      * 2. 返回第一个唯一字符索引,马上想到顺序遍历string，下标从0开始，这个是连续的。注意遍历不是hash表
      * 3. 为什么不用排序，排序后原始位置发送改变。
      */
    int firstUniqChar(string s) {

      //01 n=26 数据量很少,此时数组性能高于hashmap
      int hash[26]={0}; 
      for(auto temp:s)
      {
          hash[temp-'a']++; //假如当前是'a'-'a'=0, 第一个字母放到第一个位置
      }

      //02 遍历hash遇到第一个不是期望的结果
      for(int i=0;i<s.size();i++)
      {
           if( hash[s[i]-'a'] == 1)
           {
               return i;
           }
      }
     return -1;
    }
};
// @lc code=end

