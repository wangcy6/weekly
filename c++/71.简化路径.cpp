/*
 * @lc app=leetcode.cn id=71 lang=cpp
 *
 * [71] 简化路径
 *
 * https://leetcode-cn.com/problems/simplify-path/description/
 *
 * algorithms
 * Medium (38.98%)
 * Likes:    135
 * Dislikes: 0
 * Total Accepted:    36.7K
 * Total Submissions: 93.6K
 * Testcase Example:  '"/home/"'
 *
 * 以 Unix 风格给出一个文件的绝对路径，你需要简化它。或者换句话说，将其转换为规范路径。
 * 
 * 在 Unix 风格的文件系统中，一个点（.）表示当前目录本身；此外，两个点 （..）
 * 表示将目录切换到上一级（指向父目录）；两者都可以是复杂相对路径的组成部分。更多信息请参阅：Linux / Unix中的绝对路径 vs 相对路径
 * 
 * 请注意，返回的规范路径必须始终以斜杠 / 开头，并且两个目录名之间必须只有一个斜杠 /。最后一个目录名（如果存在）不能以 /
 * 结尾。此外，规范路径必须是表示绝对路径的最短字符串。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入："/home/"
 * 输出："/home"
 * 解释：注意，最后一个目录名后面没有斜杠。
 * 
 * 
 * 示例 2：
 * 
 * 输入："/../"
 * 输出："/"
 * 解释：从根目录向上一级是不可行的，因为根是你可以到达的最高级。
 * 
 * 
 * 示例 3：
 * 
 * 输入："/home//foo/"
 * 输出："/home/foo"
 * 解释：在规范路径中，多个连续斜杠需要用一个斜杠替换。
 * 
 * 
 * 示例 4：
 * 
 * 输入："/a/./b/../../c/"
 * 输出："/c"
 * 
 * 
 * 示例 5：
 * 
 * 输入："/a/../../b/../c//.//"
 * 输出："/c"
 * 
 * 
 * 示例 6：
 * 
 * 输入："/a//b////c/d//././/.."
 * 输出："/a/b/c"
 * 1. 不理解题目含义。感觉无从下手，空白 没哟思路，这个感觉太不是题目
 * 2. 看别人答案 说天花乱坠，看着拿过理解不了，甚至出现状态机的说法。
 * 3. 思路很简单，先将整个路径按照/分开来，然后用一个栈，
 *   遇到..时弹出一个，遇到.和空字符串则不变，遇到正常路径则压入栈中
 */

// @lc code=start
class Solution
{
public:
    string simplifyPath(string path)
    {
        path += '/';
        stack<string> temp_stack;
        string temp_string;
        //基本操作：字符串的遍历
        for (auto c : path)
        {
            //两个'/'之间为单级目录子串
            if (c == '/')
            {
                //地址从前向后跳转，如两个'/'之间的地址字符串是“..”，切换上一级目录，即将最后压入的一级目录弹出
                if (temp_string == "..")
                {
                    if (!temp_stack.empty())
                        temp_stack.pop();
                    //考虑特殊情况，如果前面没有进入子目录，一开始就是".."，此时既不能压入栈也无法弹出，需要排除，不做操作即可
                }
                //其他情况，如两个'/'之间的地址字符串存在，且不为'.'（同级目录，无变化），必为字母组成的地址，因此压入栈
                else if (temp_string != "." && !temp_string.empty())
                {
                    temp_stack.push(temp_string);
                }
                //清空单级目录字符串，准备记录下两个'/'之间的目录字符串
                temp_string.clear();
            }
            //记录单级目录字符串
            else
            {
                temp_string.push_back(c);
            }
        }
        //从栈中取出各级目录子串，加上'/'形成完整地址
        string result;
        while (!temp_stack.empty())
        {
            result = '/' + temp_stack.top() + result;
            temp_stack.pop();
        }
        //特殊情况，栈中无元素，没有扫描到有效地址，则返回'/'
        if (result.empty())
            result = "/";
        return result;
    }
};
// @lc code=end
