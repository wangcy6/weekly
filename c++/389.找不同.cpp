/*
 * @lc app=leetcode.cn id=389 lang=cpp
 *
 * [389] 找不同
 * https://leetcode-cn.com/problems/find-the-difference/description/
 *
 * algorithms
 * Easy (61.30%)
 * Likes:    125
 * Dislikes: 0
 * Total Accepted:    28K
 * Total Submissions: 45.2K
 * Testcase Example:  '"abcd"\n"abcde"'
 *
 * 给定两个字符串 s 和 t，它们只包含小写字母。
 * 
 * 字符串 t 由字符串 s 随机重排，然后在随机位置添加一个字母。
 * 
 * 请找出在 t 中被添加的字母。
 * 
 * 
 * 
 * 示例:
 * 
 * 输入：
 * s = "abcd"
 * t = "abcde"
 * 
 * 输出：
 * e
 * 
 * 解释：
 * 'e' 是那个被添加的字母。
 * 
 * 01 t比s多一个单词
 * 02 遍历t，判断s存在不存在。o(n2)，最坏情况S无限长，t无限长。完全颠倒顺序
 * 03  字符个数有限的。
 * 04 字符出现情况 
 *   都过都没在 st出现 ---0
 *   都是都出现了  ---i 一样的。
 *   都过t出现了，s没出现， 多一个。
 *   随机重排 跟顺序没有关系。
 */

// @lc code=start
class Solution
{
public:
    /***
     *  随机重排， 说明跟顺序无关系，采用hash存储
     *  然后在随机位置添加一个字母 存在最好情况，最坏情况判断.先统计字符少的。
     * */
    char findTheDifference(string s, string t)
    {

        int hash[26] = {0}; //用数组替代哈希表,一般来说元素位置和规模无关系。

        //统计字符s出现次数
        for (int i = 0; i < s.size(); i++)
        {
            hash[s[i] - 'a']++;
        }

        //减去字符t出现的次数，三个情况 都不存在 0-0=0 ，都存在 i-i=0,t比s多一个单词 0-1=-1
        for (int i = 0; i < t.size(); i++)
        {

            hash[t[i] - 'a']--;
            if (-1 == hash[t[i] - 'a'])
            {
                return t[i];
            }
        }

        return -1;
    }
};
// @lc code=end
