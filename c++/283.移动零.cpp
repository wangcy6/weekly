/*
 * @lc app=leetcode.cn id=283 lang=cpp
 *
 * [283] 移动零
 *
 * https://leetcode-cn.com/problems/move-zeroes/description/
 *
 * algorithms
 * Easy (60.29%)
 * Likes:    563
 * Dislikes: 0
 * Total Accepted:    136K
 * Total Submissions: 224.6K
 * Testcase Example:  '[0,1,0,3,12]'
 *
 * 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
 * 
 * 示例:
 * 
 * 输入: [0,1,0,3,12]
 * 输出: [1,3,12,0,0]
 * 
 * 说明:
 * 
 * 
 * 必须在原数组上操作，不能拷贝额外的数组。
 * 尽量减少操作次数。
 * 
 * 看似容易，其实很描述具体实现过程。
 * 
 * 1 如何确定 结束的位置，因为后面几个字符串都是0 
 * 2、将所有非 0 元素置于数组前面，保持它们的相对顺序相同
 * 3 大小不变
 */

// @lc code=start
class Solution {
public:
    /***
     * 1 
     **/ 
    void moveZeroes(vector<int>& nums) {
        
      int slow =0;//待插入元素
      for(int i=0;i<nums.size();i++)
      {
         if(nums[i] !=0)
         {
              nums[slow++] =nums[i];
         }
      }

      for(int i=nums.size()-1;i>=slow;i--)
      {
          nums[i] =0;
      }
    }
};
// @lc code=end

