/*
 * @lc app=leetcode.cn id=93 lang=cpp
 *
 * [93] 复原IP地址
 *
 * https://leetcode-cn.com/problems/restore-ip-addresses/description/
 *
 * algorithms
 * Medium (46.33%)
 * Likes:    263
 * Dislikes: 0
 * Total Accepted:    40.8K
 * Total Submissions: 87.5K
 * Testcase Example:  '"25525511135"'
 *
 * 给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。
 * 
 * 有效的 IP 地址正好由四个整数（每个整数位于 0 到 255 之间组成），整数之间用 '.' 分隔。
 * 
 * 
 * 
 * 示例:
 * 
 * 输入: "25525511135"
 * 输出: ["255.255.11.135", "255.255.111.35"]
 * 
 */

// @lc code=start
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> ans;
        string str;
        int len = s.size();
        dfs(s,str,0,len,0,ans);
        return ans;
    }

    void dfs(string &s,string str,int pos,int &len,int ac,vector<string> &ans){
        if(ac == 3){
            if(len <= pos)
                return;
            else if(len - pos>3)
                return;
            else if(s[pos]=='0'){
                if(pos == len -1){
                    str += s.substr(pos,len-pos);
                    ans.emplace_back(str);}
            }
            else if(len - pos <3){
                str += s.substr(pos,len-pos);
                ans.emplace_back(str);
            }
            else if(s[pos]== '1' || (s[pos]=='2' && (s[pos+1]<'5' || (s[pos+1]=='5'&&s[pos+2]<'6')))){
                str += s.substr(pos,len-pos);
                ans.emplace_back(str);
            }
        }
        else{
            if(s[pos]=='0')
                dfs(s,str+s.substr(pos,1)+'.',pos+1,len,ac+1,ans);
            else{
                if(pos < len-1)
                    dfs(s,str+s.substr(pos,1)+'.',pos+1,len,ac+1,ans);
                if(pos+1 < len-1)
                    dfs(s,str+s.substr(pos,2)+'.',pos+2,len,ac+1,ans);
                if(pos+2 < len-1){
                    if(s[pos]== '1' || (s[pos]=='2' && (s[pos+1]<'5' || (s[pos+1]=='5'&&s[pos+2]<'6'))))
                        dfs(s,str+s.substr(pos,3)+'.',pos+3,len,ac+1,ans);
            }
            
            }
        }
    }
};


// @lc code=end

