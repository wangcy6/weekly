/*
 * @lc app=leetcode.cn id=90 lang=cpp
 *
 * [90] 子集 II
 *
 * https://leetcode-cn.com/problems/subsets-ii/description/
 *
 * algorithms
 * Medium (59.53%)
 * Likes:    218
 * Dislikes: 0
 * Total Accepted:    32.3K
 * Total Submissions: 54K
 * Testcase Example:  '[1,2,2]'
 *
 * 给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
 * 
 * 说明：解集不能包含重复的子集。
 * 
 * 示例:
 * 
 * 输入: [1,2,2]
 * 输出:
 * [
 * ⁠ [2],
 * ⁠ [1],
 * ⁠ [1,2,2],
 * ⁠ [2,2],
 * ⁠ [1,2],
 * ⁠ []
 * ]
 * 
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> result;
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> tmp(nums.size());
        subsetsWithDup(nums, tmp, 0, 0);
        return result;
    }

    void subsetsWithDup(vector<int>& nums, vector<int>& tmp, int pos, int t_pos) {
        if (pos >= nums.size()) {
            result.emplace_back(vector<int>(tmp.begin(), tmp.begin() + t_pos));
            return;
        }
        tmp[t_pos] = nums[pos];
        subsetsWithDup(nums, tmp, pos+1, t_pos+1);     // 选择当前数
        while (pos+1 < nums.size() && nums[pos] == nums[pos+1]) pos ++;   // 不选择当前数时，后续相等的数也要跳过
        subsetsWithDup(nums, tmp, pos+1, t_pos);
    }
};

// @lc code=end

