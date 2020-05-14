/*
 * @lc app=leetcode.cn id=49 lang=cpp
 *
 * [49] 字母异位词分组
 *
 * https://leetcode-cn.com/problems/group-anagrams/description/
 *
 * algorithms
 * Medium (61.24%)
 * Likes:    329
 * Dislikes: 0
 * Total Accepted:    69.2K
 * Total Submissions: 112.9K
 * Testcase Example:  '["eat","tea","tan","ate","nat","bat"]'
 *
 * 给定一个字符串数组，将字母异位词组合在一起。字母异位词指字母相同，但排列不同的字符串。
 * 
 * 示例:
 * 
 * 输入: ["eat", "tea", "tan", "ate", "nat", "bat"]
 * 输出:
 * [
 * ⁠ ["ate","eat","tea"], 
 * ⁠ ["nat","tan"],
 * ⁠ ["bat"]
 * ]
 * 
 * 说明：
 * 
 * 
 * 所有输入均为小写字母。
 * 不考虑答案输出的顺序。
 * 
 * 
 */

// @lc code=start
class Solution {
public:
     //最基本思路，能保证运行正确，但是不是最优的
     //时间复杂度：O(NKlog K)
     //方法一：排序数组分类
    vector<vector<string>> groupAnagrams(vector<string>& strs) {

      unordered_map<string,vector<string>> hashmap; //异位词组放在一起，马上联想到hashmap 
      vector<vector<string>>  res;
      for(auto temp:strs)
      {
           string key=temp;
           sort(key.begin(),key.end()); //class Hash = hash<Key>,
          hashmap[key].push_back(temp); //第一次插入一个元素时候，判断存在不存在。
         // hashmap.at(key).push_back(temp);  //throwing an instance of 'std::out_of_range'
      }


      for(auto& i:hashmap )
      {
          res.push_back(i.second);
      }

      return res;


    }
};
// @lc code=end

