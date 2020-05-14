/*
 * @lc app=leetcode.cn id=68 lang=cpp
 *
 * [68] 文本左右对齐
 *
 * https://leetcode-cn.com/problems/text-justification/description/
 *
 * algorithms
 * Hard (42.96%)
 * Likes:    65
 * Dislikes: 0
 * Total Accepted:    8K
 * Total Submissions: 18.5K
 * Testcase Example:  '["This", "is", "an", "example", "of", "text", "justification."]\n16'
 *
 * 给定一个单词数组和一个长度 maxWidth，重新排版单词，使其成为每行恰好有 maxWidth 个字符，且左右两端对齐的文本。
 * 
 * 你应该使用“贪心算法”来放置给定的单词；也就是说，尽可能多地往每行中放置单词。必要时可用空格 ' ' 填充，使得每行恰好有 maxWidth 个字符。
 * 
 * 要求尽可能均匀分配单词间的空格数量。如果某一行单词间的空格不能均匀分配，则左侧放置的空格数要多于右侧的空格数。
 * 
 * 文本的最后一行应为左对齐，且单词之间不插入额外的空格。
 * 
 * 说明:
 * 
 * 
 * 单词是指由非空格字符组成的字符序列。
 * 每个单词的长度大于 0，小于等于 maxWidth。
 * 输入单词数组 words 至少包含一个单词。
 * 
 * 
 * 示例:
 * 
 * 输入:
 * words = ["This", "is", "an", "example", "of", "text", "justification."]
 * maxWidth = 16
 * 输出:
 * [
 * "This    is    an",
 * "example  of text",
 * "justification.  "
 * ]
 * 
 * 
 * 示例 2:
 * 
 * 输入:
 * words = ["What","must","be","acknowledgment","shall","be"]
 * maxWidth = 16
 * 输出:
 * [
 * "What   must   be",
 * "acknowledgment  ",
 * "shall be        "
 * ]
 * 解释: 注意最后一行的格式应为 "shall be    " 而不是 "shall     be",
 * 因为最后一行应为左对齐，而不是左右两端对齐。       
 * ⁠    第二行同样为左对齐，这是因为这行只包含一个单词。
 * 
 * 
 * 示例 3:
 * 
 * 输入:
 * words =
 * ["Science","is","what","we","understand","well","enough","to","explain",
 * "to","a","computer.","Art","is","everything","else","we","do"]
 * maxWidth = 20
 * 输出:
 * [
 * "Science  is  what we",
 * ⁠ "understand      well",
 * "enough to explain to",
 * "a  computer.  Art is",
 * "everything  else  we",
 * "do                  "
 * ]
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> ans;
        string s="";
        int cur_length=0;//当前行已经填补的字母个数
        int lineNum=0;//一行中单词的个数
        int i=0;
        while(i<words.size()){
            if(cur_length+words[i].length()<=maxWidth){//当该行可以放置下一个单词时
                cur_length+=words[i].length();//当前长度加上单词的长度
                s+=words[i];
                lineNum++;//单词个数+1
                if(cur_length<maxWidth){
                    cur_length++;
                    s+=" ";
                }
                else if(cur_length==maxWidth){//当前长度正好=maxWidth
                    ans.push_back(s);//保存
                    s="";
                    cur_length=0;
                    lineNum=0;//清空参数，重新记录
                }
                i++;
            }
            else{//否则
                cur_length--;
                s.erase(s.end()-1);//去除字符串s末尾的空格
                int blocknum=maxWidth-cur_length;//计算要补全多少个空格
                if(lineNum==1){//如果一行只有一个单词
                    string blockstr(blocknum,' ');
                    s+=blockstr;
                    ans.push_back(s);//直接在s后补齐blocknum个空格
                    lineNum=0;
                    cur_length=0;
                    s="";//清空参数，重新记录
                }
                else{//计算每两个单词之间需要补充的空格个数
                    vector<int> blocks(lineNum-1,0);
                    int j=lineNum-2;
                    for(;j>=0;j--){
                        blocks[j]=blocknum/(lineNum-1);
                        blocknum-=blocks[j];
                        lineNum--;
                    }//计算每个位置补充的空格个数，从后往前计算
                    int cur=0,wordpos=i-blocks.size()-1;
                    //wordpos为当前行单词的起始位置，cur为补充空格的位置
                    for(j=0;j<blocks.size();j++){
                        cur+=(words[wordpos].length()+1);
                        string bstr=string(blocks[j],' ');
                        s.insert(cur,bstr);
                        cur+=blocks[j];
                        wordpos++;
                    }
                    ans.push_back(s);
                    lineNum=0;
                    cur_length=0;
                    s="";//清空参数，重新记录
                }
                
            }
        }
        if(cur_length!=0){//若存在未记录的文本
            string blockstr(maxWidth-cur_length,' ');
            s+=blockstr;
            ans.push_back(s);
        }
        return ans;
    }
};

// @lc code=end

