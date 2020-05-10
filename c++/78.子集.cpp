/*
 * @lc app=leetcode.cn id=78 lang=cpp
 *
 * [78] 子集
 *
 * https://leetcode-cn.com/problems/subsets/description/
 *
 * algorithms
 * Medium (77.08%)
 * Likes:    556
 * Dislikes: 0
 * Total Accepted:    84.7K
 * Total Submissions: 109.8K
 * Testcase Example:  '[1,2,3]'
 *
 * 给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
 * 
 * 说明：解集不能包含重复的子集。
 * 
 * 示例:
 * 
 * 输入: nums = [1,2,3]
 * 输出:
 * [
 * ⁠ [3],
 * [1],
 * [2],
 * [1,2,3],
 * [1,3],
 * [2,3],
 * [1,2],
 * []
 * ]
 * 
 * //Approach 1: 感觉解题
 * https://leetcode.com/problems/subsets/solution/
 * 
 * bug1
 * https://www.cnblogs.com/qingjiaowoxiaoxioashou/p/5874572.html
//  * while (it != v.end())
//     {
//         if (*it % 2 == 0)
//         {
//             it = v.erase(it);
//         }
//         else
//         {
//             ++it;
//         }
        
//     }
 * Approach 2: Backtracking
 * //递归回溯
 * 递归：全部考虑，选或不选
 * https://leetcode-cn.com/problems/subsets/solution/hot-100-78zi-ji-python3-hui-su-liang-chong-jie-ti-/
 *
 * 递归： 情况一：集合中有该元素
 * https://leetcode-cn.com/problems/subsets/solution/c-0ms-132mb-shen-sou-yong-shi-ji-bai-100mark-by-is/
 * https://leetcode-cn.com/problems/subsets/solution/hui-su-si-xiang-tuan-mie-pai-lie-zu-he-zi-ji-wen-t/
 * 算法

Approach 3: Backtracking
https://leetcode-cn.com/problems/subsets/solution/hui-su-si-xiang-tuan-mie-pai-lie-zu-he-zi-ji-wen-t/ 


*/

// @lc code=start
class Solution
{
public:
   //思路: 标准递归回溯
   //时间复杂度:   0 ms
   //思路描述：
   // def backtrack(路径, 选择列表):
   //  if 满足结束条件:
   //      result.add(路径)
   //      return
   //  for 选择 in 选择列表:
   //      做选择
   //      backtrack(路径, 选择列表)
   //      撤销选择

   vector<vector<int>> subsets(vector<int> &nums)
   {
      vector<vector<int>> res; //输出结果集合
      vector<int> path;        //定义变量path  代表递归路径.
      int start = 0;           //定义变量start,标记访问位置，因为目标是集合，不要求排序，i>=start，没有被访问。
                               //<start 代表已经访问，这样清晰区分。{1,3} {3,1} 同一个集合
                             

      //递归回溯。start也可理解tree的高度 start =0,代表空元素。一个元素都没有选择。
      //每次递归，从剩余元素选择。和全排不一样地方，<start 回溯标记已经使用过。
      //start 0 ，剩余 {1 2 3 }
      //start 1 ，剩余 {2,3}
      //start 2 ，剩余 {3}
      //end
      //{1,2 3} -->4  {2 ,3}-->2  {3 } -->1
      dfs(path, start, nums, res);

      return res;
   }

   void dfs(vector<int> &path, int start, vector<int> &nums, vector<vector<int>> &res)
   {
      //N叉树的每个节点都是集合，不仅仅是叶子节点。
      res.push_back(path);
      if (start == nums.size())
      {
         return; //以防万一，其实这一步可以舍去，每次循环i=start开始，【start，n】
         //start=0,固定不变造成死循环。
      }

      for (int i = start; i < nums.size(); i++)
      {
         //这里求子集 不是全排序，通过start来过滤已经访问元素？
         //每次递归，从剩余元素选择。和全排不一样地方，<start 回溯标记已经使用过。全排需要used标记
         //start 0 ，剩余 {1 2 3 }
         //start 1 ，剩余 {2,3}
         //start 2 ，剩余 {3}
         //start 3 ，start 永远不等于3，for循环控制呢.[0,n-1]
         path.push_back(nums[i]); //
         //写错误了，每次从i开始。
         dfs(path, i + 1, nums, res);
         //dfs(path, start + 1, nums, res); 正的变身死循环了。小心呀
         //void pop_back(); Delete last element
         path.pop_back(); //出栈，回到start层样子
      }
   }
   //思路: 感觉解题
   //时间复杂度:  4ms 不会预估
   //思路描述：每添加一个新元素，增加i+1个组合 数学归纳，直接观察得到结论
   vector<vector<int>> subsets2(vector<int> &nums)
   {
      vector<vector<int>> res; //输出结果

      // 01 遍历数组,获取当前元素
      for (auto num : nums)
      {
         //02 每添加一个新元素，增加n+1个组合
         vector<vector<int>> addItem; // 新增集合
         //03 添加新增元素+1
         vector<int> cur(1, num);
         addItem.push_back(cur);

         //04 n 历史元素
         for (auto cur : res)
         {
            //为什么不直接遍历res,
            // vector迭代器的几种失效的情况：
            // 1.当插入（push_back）一个元素后，end操作返回的迭代器肯定失效。
            // 2.当插入(push_back)一个元素后，capacity返回值与没有插入元素之前相比有改变，则需要重新加载整个容器，此时first和end操 作返回的迭代器都会失效。
            // 3.当进行删除操作（erase，pop_back）后，指向删除点的迭代器全部失效；指向删除点后面的元素的迭代器也将全部失效。
            cur.push_back(num);
            addItem.push_back(cur);
         }

         //新增集合添加到输出结果
         for (auto i : addItem)
         {
            res.push_back(i);
         }
      }
      vector<int> empty; //别忘记空集和
      res.push_back(empty);
      return res;
   }

   //自觉做题为什么对呀？没考虑间隔的.这个怎么办
   vector<vector<int>> subsets1(vector<int> &nums)
   {

      vector<vector<int>> res;

      for (int i = 0; i < nums.size(); i++)
      {
         vector<int> temp;
         for (int j = i; j < nums.size(); j++)
         {
            temp.push_back(nums[j]);
            res.push_back(temp); //[1,3] [],
         }
      }

      return res;
   }
};
// @lc code=end
