/*
 * @lc app=leetcode.cn id=76 lang=cpp
 *
 * [76] 最小覆盖子串
 *
 * https://leetcode-cn.com/problems/minimum-window-substring/description/
 *
 * algorithms
 * Hard (35.63%)
 * Likes:    453
 * Dislikes: 0
 * Total Accepted:    37K
 * Total Submissions: 103.4K
 * Testcase Example:  '"ADOBECODEBANC"\n"ABC"'
 *
 * 给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字母的最小子串。
 * 
 * 示例：
 * 
 * 输入: S = "ADOBECODEBANC", T = "ABC"
 * 输出: "BANC"
 * 
 * 说明：
 * 
 * 
 * 如果 S 中不存这样的子串，则返回空字符串 ""。
 * 如果 S 中存在这样的子串，我们保证它是唯一的答案。
 * 
 * 无从下手，感觉恐慌，或者提供不可能思想
 * https://leetcode-cn.com/problems/minimum-window-substring/solution/hua-chuang-fa-by-coldme-2/
 */

// @lc code=start
class Solution {
public:
    string minWindow(string s, string t) {
        // 初始化counter_s和counter_t
        unordered_map<char, int> counter_t, counter_s;
        for (char c : t) {
            counter_t[c]++;
        }

        int left = 0, valid = 0;
        // 记录最小覆盖子串的起始索引及长度
        int start = -1, minlen = INT_MAX;
        for (int right = 0; right < s.size(); right ++){
            // 移动右边界, ch 是将移入窗口的字符
            char ch = s[right];
            if (counter_t.count(ch)) {
                counter_s[ch]++;
                if (counter_s[ch] == counter_t[ch])
                    valid++;
            }

            // 判断左侧窗口是否要收缩
            while (valid == counter_t.size()) {
                // 更新最小覆盖子串
                if (right - left < minlen) {
                    start = left;
                    minlen = right - left;
                }
            // left_ch 是将移出窗口的字符
            char left_ch = s[left];
            // 左移窗口
            left ++;
            // 进行窗口内数据的一系列更新
            if (counter_t.count(left_ch)) {
                if (counter_s[left_ch] == counter_t[left_ch])
                    valid--;
                counter_s[left_ch] --;
            }                    
        }
    }
    // 返回最小覆盖子串
    return start == -1 ? "" : s.substr(start, minlen + 1);
    }
};
// @lc code=end

