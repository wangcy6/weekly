/*
 * @lc app=leetcode.cn id=88 lang=cpp
 *
 * [88] 合并两个有序数组
 *
 * https://leetcode-cn.com/problems/merge-sorted-array/description/
 *
 * algorithms
 * Easy (47.24%)
 * Likes:    479
 * Dislikes: 0
 * Total Accepted:    136.9K
 * Total Submissions: 289.2K
 * Testcase Example:  '[1,2,3,0,0,0]\n3\n[2,5,6]\n3'
 *
 * 给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。
 * 
 * 
 * 
 * 说明:
 * 
 * 
 * 初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。
 * 你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。
 * 
 * 
 * 
 * 
 * 示例:
 * 
 * 输入:
 * nums1 = [1,2,3,0,0,0], m = 3
 * nums2 = [2,5,6],       n = 3
 * 
 * 输出: [1,2,2,3,5,6]
 * 
 */

// @lc code=start
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int tag=m+n-1,i=m-1,j=n-1;
        for(;i>=0&&j>=0;){
            if(nums1[i]>=nums2[j]){
                nums1[tag--]=nums1[i];
                i--;
            }
            else{
                nums1[tag--]=nums2[j];
                j--;
            }
        }
        if(i<0){
            while(j>=0){
                nums1[tag--]=nums2[j--];
            }
        }
        else{
            while(i>=0){
                nums1[tag--]=nums1[i--];
            }
        }
        for(int i=0;i<m+n;i++){
            cout<<nums1[i];
        }
    }
};
// @lc code=end

