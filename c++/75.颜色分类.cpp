/*
 * @lc app=leetcode.cn id=75 lang=cpp
 *
 * [75] 颜色分类
 *
 * https://leetcode-cn.com/problems/sort-colors/description/
 *
 * algorithms
 * Medium (54.69%)
 * Likes:    405
 * Dislikes: 0
 * Total Accepted:    77.7K
 * Total Submissions: 141.6K
 * Testcase Example:  '[2,0,2,1,1,0]'
 *
 * 给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
 * 
 * 此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。
 * 
 * 注意:
 * 不能使用代码库中的排序函数来解决这道题。
 * 
 * 示例:
 * 
 * 输入: [2,0,2,1,1,0,1]
 * 输出: [0,0,1,1,1,2,2]
 * 
 * 进阶：
 * 
 * 
 * 一个直观的解决方案是使用计数排序的两趟扫描算法。
 * 首先，迭代计算出0、1 和 2 元素的个数，然后按照0、1、2的排序，重写当前数组。
 * 你能想出一个仅使用常数空间的一趟扫描算法吗？
 * 
 * 题目 
 * 1 不太理解，自己sort可以了吗？关什么颜色，颜色有啥关系。
 * 2.你了解 排序算法。排序时候考虑元素：重复不重复
 * 3. 有重复元素的排列问题
 * 
 *   
 * 
 * 
 * 
 */

/**     https://www.jianshu.com/p/779bc4b61254
 *      
           left part           center part                   right part
        * +--------------------------------------------------------------+
        * |  < pivot   |          ==pivot         |    ?    |  > pivot  |
        * +--------------------------------------------------------------+
        *              ^                          ^         ^
        *              |                          |         |
        *              lt                         i        gt
        * 
    通过维持三个指针来控制[left, lt )小于主元(pivot)，[lt, i)等于主元，[i, gt]未知，(gt, right]大于主元。

  一开始，lt指向主元的位置left，gt指向right，而i从left右边接下来的第一个索引开始遍历，每当遇到一个数，就判断它与主元之间的大小关系，有三种情况：

1 小于主元就把这个数与lt指向的数交换，然后lt,i都自增1，然后继续遍历
2 大于主元就把这个数与gt指向的数交换，gt自减1，此时i还得不能自增，因为它不知道gt用一个什么样的元素跟它交换，所以留到下一次循环判断交换过来的这个元素的去留
3 等于主元就不用跟谁进行交换，直接自增1就可以
https://wiesen.github.io/post/%E5%BF%AB%E9%80%9F%E6%8E%92%E5%BA%8F%E7%AC%94%E8%AE%B0/

**/

// @lc code=start
class Solution
{
public:
  /**
     * 算法描述：
     * 
     **/
  void sortColors(vector<int> &nums)
  {

    int low = 0;                // < pivot
    int high = nums.size() - 1; //> pivot
    int mid = 0;                //  ==pivot

    while (mid <= high)
    {
      if (nums[mid] == 1)
      {
        mid++; //等于，不移动
      }
      else if (nums[mid] > 1)
      {
        //从左边发现大记录，需要移动右面去,nums[mid]很明确了 =2，
        //原来high位置元素具体不清楚的。可能等于因此swap mid位置不变

        swap(nums,mid, high);
        high--;
      }
      else if (nums[mid] < 1)
      {
        //从右面发现大记录，需要移动左边去。 nums[mid]很明确=0，可能自己的，可能上面过来的。low 肯定也是0.
        swap(nums,mid, low);
        low++;
        mid++;
      }
    }
  }

  void swap(vector<int> &nums,int i,int j)
  {
     int temp =nums[i];
     nums[i] =nums[j];
     nums[j] =temp;
  }
};
// @lc code=end
