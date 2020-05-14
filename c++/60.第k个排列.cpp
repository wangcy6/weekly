/*
 * @lc app=leetcode.cn id=60 lang=cpp
 *
 * [60] 第k个排列
 *
 * https://leetcode-cn.com/problems/permutation-sequence/description/
 *
 * algorithms
 * Medium (48.51%)
 * Likes:    233
 * Dislikes: 0
 * Total Accepted:    31.6K
 * Total Submissions: 65K
 * Testcase Example:  '3\n3'
 *
 * 给出集合 [1,2,3,…,n]，其所有元素共有 n! 种排列。
 * 
 * 按大小顺序列出所有排列情况，并一一标记，当 n = 3 时, 所有排列如下：
 * 
 * 
 * "123"
 * "132"
 * "213"
 * "231"
 * "312"
 * "321"
 * 
 * 
 * 给定 n 和 k，返回第 k 个排列。
 * 
 * 说明：
 * 
 * 
 * 给定 n 的范围是 [1, 9]。
 * 给定 k 的范围是[1,  n!]。
 * 
 * 
 * 示例 1:
 * 
 * 输入: n = 3, k = 3
 * 输出: "213"
 * 
 * 
 * 示例 2:
 * 
 * 输入: n = 4, k = 9
 * 输出: "2314"
 * 
 * //如果把all排列都组合起来，这样太多了。
 * //根据上面规律结合全排列46题目，排序输出后的
 * 
 * 
 */

// @lc code=start
class Solution
{
public:

        string getPermutation(int n, int k) {
        string s = string("123456789").substr(0,n);
        for(int j = 1; j < k; ++j) next_permutation(s.begin(), s.end()); //罪过 罪过, 谢罪！
        return s;
    }

    //超出时间限制 case 9!=   9 37098
    //4!=24
    string getPermutation1(int n, int k)
    {
        vector<int> nums(n);
        for (int i = 0; i < n; i++)
        {
            nums[i] = i + 1; // 代表有序1-n个记录
        }

        vector<bool> used(n, false); //判断是否标记
        int total = 0;
        string path; //路径
        string res;

        vector<int> factorial(n + 1, 0); ///n！
        factorial[0] = 1;

        for (int i = 1; i <= n; i++)
        {
            factorial[i] = factorial[i - 1] * i;
        }

        dfs(total, k, 0, nums, used, path, res, factorial);
        cout << res << endl;
        return res;
    }

    void dfs(int &total, int &k, int level, vector<int> &nums, vector<bool> &used, string &path, string &res, vector<int> &factorial)
    {
        if (level == nums.size())
        {
            total++;
            if (total == k)
            {
                res = path;
            }

            return;
        }
        int count = factorial[nums.size() - 1 - level];
        for (int i = 0; i < nums.size(); i++)
        {
            if (used[i] == true)
            {
                continue;
            }

            //减枝 没必要都要计算
            if ((k - total) > count)
            {
                total += count; //类似满二叉tree，可以计算一共有多个节点。
                continue;
            }

            used[i] = true;
            path.push_back(nums[i] + '0');

            dfs(total, k, level + 1, nums, used, path, res, factorial);

            used[i] = false;
            path.pop_back();
        }
    }
};
// @lc code=end
