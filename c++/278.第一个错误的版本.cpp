/*
 * @lc app=leetcode.cn id=278 lang=cpp
 *
 * [278] 第一个错误的版本
 *
 * https://leetcode-cn.com/problems/first-bad-version/description/
 *
 * algorithms
 * Easy (37.81%)
 * Likes:    158
 * Dislikes: 0
 * Total Accepted:    42.9K
 * Total Submissions: 113.3K
 * Testcase Example:  '5\n4'
 *
 * 
 * 你是产品经理，目前正在带领一个团队开发新的产品。不幸的是，你的产品的最新版本没有通过质量检测。由于每个版本都是基于之前的版本开发的，所以错误的版本之后的所有版本都是错的。
 * 
 * 假设你有 n 个版本 [1, 2, ..., n]，你想找出导致之后所有版本出错的第一个错误的版本。
 * 
 * 你可以通过调用 bool isBadVersion(version) 接口来判断版本号 version
 * 是否在单元测试中出错。实现一个函数来查找第一个错误的版本。你应该尽量减少对调用 API 的次数。
 * 
 * 示例:
 * 
 * 给定 n = 5，并且 version = 4 是第一个错误的版本。
 * 
 * 调用 isBadVersion(3) -> false
 * 调用 isBadVersion(5) -> true
 * 调用 isBadVersion(4) -> true
 * 
 * 所以，4 是第一个错误的版本。 
 *
 * 第一次：
 *  这个还需要计算吗？直接数据存储，然后查询结果就什么？难道还有其他问题办法吗？
 *  题目啥意思呢
 *  是否在单元测试中出错。实现一个函数来查找第一个错误的版本。你应该尽量减少对调用 API 的次数。
 *  
 * 最少调用次数 ，
 *  bool isBadVersion(version) 接口来判断版本号 version 已经给出结果了。
 * 让你在使用上面基础上最少调用次数。 
 * 从左到右寻找第一个isBadVersion返回true
 * 
 * 第二次分析：
 * 
 *  场景一：isBadVersion(mid) => false

    1 2 3 4 5 6 7 8 9
    G G G G G G B B B       G = 正确版本，B = 错误版本
    |       |       |
    left    mid    right

    场景二：isBadVersion(mid) => true

    1 2 3 4 5 6 7 8 9
    G G G B B B B B B       G = 正确版本，B = 错误版本
    |       |       |
    left    mid    right


 */

// @lc code=start
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);
//n=2126753390
class Solution {
public:
    int firstBadVersion(int n) {
        
        long left =1;//不是从0开始的，版本号是从1开始的
        long right =n;
        //循环条件：left ==right 说明就是目标了
        //从左到右寻找第一个isBadVersion返回true
        //陷阱：
        //isBadVersion(3)  返回值只有2个，
        //和平时理解这么不一样 大于 等于 小于依然继续使用。
        while(left < right)
        {
         long mid=(left+right)/2;
        
         // mid版本是正确版本，肯定不是错误版本
         if(isBadVersion(mid) ==false)
         {
            left =mid+1;//
         }else{
             right =mid;//mid是错误版本，不确定是否第一个错误的。
         }
        }
        return left;
    }
};
// @lc code=end

