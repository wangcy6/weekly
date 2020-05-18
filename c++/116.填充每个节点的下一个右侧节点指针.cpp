/*
 * @lc app=leetcode.cn id=116 lang=cpp
 *
 * [116] 填充每个节点的下一个右侧节点指针
 *
 * https://leetcode-cn.com/problems/populating-next-right-pointers-in-each-node/description/
 *
 * algorithms
 * Medium (57.24%)
 * Likes:    168
 * Dislikes: 0
 * Total Accepted:    33K
 * Total Submissions: 55.9K
 * Testcase Example:  '[1,2,3,4,5,6,7]'
 *
 * 给定一个完美二叉树，其所有叶子节点都在同一层，每个父节点都有两个子节点。二叉树定义如下：
 * 
 * struct Node {
 * ⁠ int val;
 * ⁠ Node *left;
 * ⁠ Node *right;
 * ⁠ Node *next;
 * }
 * 
 * 填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL。
 * 
 * 初始状态下，所有 next 指针都被设置为 NULL。
 * 
 * 
 * 
 * 示例：
 * 
 * 
 * 
 * 
 * 输入：{"$id":"1","left":{"$id":"2","left":{"$id":"3","left":null,"next":null,"right":null,"val":4},"next":null,"right":{"$id":"4","left":null,"next":null,"right":null,"val":5},"val":2},"next":null,"right":{"$id":"5","left":{"$id":"6","left":null,"next":null,"right":null,"val":6},"next":null,"right":{"$id":"7","left":null,"next":null,"right":null,"val":7},"val":3},"val":1}
 * 
 * 
 * 输出：{"$id":"1","left":{"$id":"2","left":{"$id":"3","left":null,"next":{"$id":"4","left":null,"next":{"$id":"5","left":null,"next":{"$id":"6","left":null,"next":null,"right":null,"val":7},"right":null,"val":6},"right":null,"val":5},"right":null,"val":4},"next":{"$id":"7","left":{"$ref":"5"},"next":null,"right":{"$ref":"6"},"val":3},"right":{"$ref":"4"},"val":2},"next":null,"right":{"$ref":"7"},"val":1}
 * 
 * 解释：给定二叉树如图 A 所示，你的函数应该填充它的每个 next 指针，以指向其下一个右侧节点，如图 B 所示。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 你只能使用常量级额外空间。
 * 使用递归解题也符合要求，本题中递归程序占用的栈空间不算做额外的空间复杂度。
 * 
 * 
 */

// @lc code=start
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution
{
public:
    Node *connect(Node *root)
    {
    }
};
// @lc code=end

class Solution
{
public:

    /***
     1 解题思路2：
       因为查询时间点，是有限的，开始时间和结束时间也是有点的 不超过1000个
       直接计算[0-1001]个点直接 全部同时学习的学生。
       For multiple queries:
       We can calculate the overlapping intervals at any time by maintaining an array that contains the intervals of all the students. 
       Doing this requires O(maxm_element + numberOfStudents) time.
     2.算法描述：
       1. 用开始时间，作为数组下标，遍历开始时间数组。count[start] += 1;
       2. 用结束时间，作为数组下标，遍历结束时间数组。 count[end + 1] -= 1;
       3. 累加：count[i] += count[i - 1];
     3.复杂度：时间 O(N),空间O(N)
    int busyStudent(vector<int> &startTime, vector<int> &endTime, int queryTime)
    {

        //作为一个服务,这里假如每次查询 startTime,endTime固定不变，变化的queryTime.
        // 如果每次startTime，endTime都是变化的，这个算法浪费空间了.
        vector<int> count(1002, 0); //key 时间点，value 10002是防止end+1越界，[0--1001]

        for (auto start : startTime)
        {
            count[start] += 1;
        }

        for (auto end : endTime)
        {
            count[end + 1] -= 1;
        }
        //[1,100],[2,100],[3,100],[4,100] 在4点，100点同时多少个学生在学习,答案就是4.在101点呢，都结束了。
        for (int i = 1; i < 1002; i++)
        {
            count[i] += count[i - 1];
        }

        return count[queryTime];
    }
};
