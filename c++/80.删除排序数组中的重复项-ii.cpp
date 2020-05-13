/*
 * @lc app=leetcode.cn id=80 lang=cpp
 *
 * [80] 删除排序数组中的重复项 II
 *
 * https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array-ii/description/
 *
 * algorithms
 * Medium (54.87%)
 * Likes:    217
 * Dislikes: 0
 * Total Accepted:    42.9K
 * Total Submissions: 77.6K
 * Testcase Example:  '[1,1,1,2,2,3]'
 *
 * 给定一个排序数组，你需要在原地删除重复出现的元素，使得每个元素最多出现两次，返回移除后数组的新长度。
 * 
 * 不要使用额外的数组空间，你必须在原地修改输入数组并在使用 O(1) 额外空间的条件下完成。
 * 
 * 示例 1:
 * 
 * 给定 nums = [1,1,1,2,2,3],
 * 
 * 函数应返回新长度 length = 5, 并且原数组的前五个元素被修改为 1, 1, 2, 2, 3 。
 * 
 * 你不需要考虑数组中超出新长度后面的元素。
 * 
 * 示例 2:
 * 
 * 给定 nums = [0,0,1,1,1,1,2,3,3],
 * 
 * 函数应返回新长度 length = 7, 并且原数组的前五个元素被修改为 0, 0, 1, 1, 2, 3, 3 。
 * 
 * 你不需要考虑数组中超出新长度后面的元素。
 * 
 * 
 * 说明:
 * 
 * 为什么返回数值是整数，但输出的答案是数组呢?
 * 
 * 请注意，输入数组是以“引用”方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。
 * 
 * 你可以想象内部操作如下:
 * 
 * // nums 是以“引用”方式传递的。也就是说，不对实参做任何拷贝
 * int len = removeDuplicates(nums);
 * 
 * // 在函数里修改输入数组对于调用者是可见的。
 * // 根据你的函数返回的长度, 它会打印出数组中该长度范围内的所有元素。
 * for (int i = 0; i < len; i++) {
 * print(nums[i]);
 * }
 * 
 */

// @lc code=start
class Solution
{
public:
    /*  解题思路：nums = [1,1,1,2,2,3]
        这个题目难点
        只要发现重复元素超过3个，删除其中一个元素时候，后面整体前移复杂度是o(n)，
        数组长度然后变小。iterator失效。
        
        换个思路：
        其实数组分配的内存大小，没有发生变化，类似redis 字符串结构 提前申请多余空间。
        还有std::unique 并不会删除任何东西，它不会改变容器的size。
        具体实： http://www.cplusplus.com/reference/algorithm/unique/
        需要一个变量标记(0,k) k有效长度。   
        
       算法描述：覆盖多余的重复项   
    
         1. 定义一个大小为3窗口。这个方法同样计数count完成
         2. 如果窗口首位元素相等。存在3个重复元素count(i)=3,需要删除一个元素。
            删除条件在步骤3
         3. 大小为3窗口，发现合法数据时候，合法数据替换重复数据。
         4 步骤 2，3重复 循环 完毕。还有最后2个剩余元素。
          自己顺序移动。
        
       复杂度分析： 12 ms o(n)
     *
     */
    int removeDuplicates(vector<int> &nums)
    {

        int n = nums.size();
        if (n <= 2)
        { // 01  如果长度小于2，无论什么样数字，都符合条件. 直接返回
            return n;
        }

        // [ ...pos....left .... right]
        int left = 0;
        int pos = 0;
        int right = 2; //默认第一个窗口,窗口大小为3 [1,1,1]
        while (right < n)
        {
            //02 如果窗口头尾元素不相等，则说明窗头元素重复度小于等于2.不需要删除记录,
            //不重复记录去覆盖重复的记录
            if (nums[right] != nums[left])
            {
                nums[pos++] = nums[left];

                //pos位置：被替换后
                //2.1如果有重复元素。 1替换1。1保持不变。
                //2.2如果不是重复元素，新元素代替重复元素位置.
                //2.2 如果全部都不相同 nums[pos] =nums[left]
            }
            //03 如果窗口头尾元素相等，说明有重复元素。重复元素超过等于3个
            //这里不直接需要删除记录，
            //技巧：删除策略：如果发现重复元素，保留第一个元素。看上面。

            right++;
            left++;
        }

        //如果全部都相同 [1,1,1,1,1,1,1] pos 不移动
        //或者right结束时候，你发现因为窗口是3，left 还有2个元素没有移动

        nums[pos++] = nums[n - 2];
        nums[pos] = nums[n - 1];
        //n <=2 合法性检查。

        return pos + 1;
    }
};
// @lc code=end

