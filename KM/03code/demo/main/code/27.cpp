#include <iostream>
#include <stack>

using namespace std;

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x)
        : val(x), left(NULL), right(NULL)
    {
    }
    TreeNode()
        : val(0), left(NULL), right(NULL)
    {
    }
};
//非递归中顺遍历
void InOrderTraverse(TreeNode* root)
{
    stack<TreeNode*> path;
    TreeNode* pcur =root;
    while (pcur!=NULL || path.empty() ==false)
    {
         while (pcur !=NULL)
         {
            path.push(pcur);
            pcur =pcur->left;
         }
         if (path.empty() ==false)
         {
            pcur = path.top();
            cout<< "pop= "<<pcur->val<<endl; 
            path.pop();

            pcur =pcur->right;
         }
         
    }

}

///////////////////////////////////////////////////////////////////////////
class Solution
{
public:
    /**
     * [Convert description]
     * @AuthorHTL wang_cyi
     * @DateTime  二〇二〇年一月八日 17:28:42
     * @param     pRootOfTree              [二叉搜索树的根]
     * @return                             [转换成双链表的头结点]
     * @how
     *  中顺遍历，只能获取currNode 和preNode。
     *  2点确定一线
     *  试图三点解决这个问题是错误的。
     */
    TreeNode* ConvertByStack(TreeNode* pRootOfTree)
    {
         if (NULL == pRootOfTree)
         {
             return NULL;
         }
   
        TreeNode* head = NULL;
        TreeNode* currNode =pRootOfTree;
        TreeNode* preNode =NULL;
        stack<TreeNode*> path;
        
        while (currNode !=NULL || !path.empty())
        {
            while (currNode !=NULL)
            {
               path.push(currNode);
               currNode = currNode->left;
            }

            if (!path.empty())
            {
                currNode = path.top();
                path.pop();

                if (preNode == NULL)
                {  //fist node
                  
                  head = currNode;
                }
                else
                {
                    // A-->B  B-->A

                    preNode->right =currNode;
                    currNode->left =preNode;

                }
                
                preNode =currNode;
                currNode = currNode->right;
            }
            
            
        }
        
        return head;
          
    }
};
int main()
{
    //    4
    //  3   5
    //2
    TreeNode tree[4];
    tree[0].val = 4;
    tree[0].left = &tree[1];
    tree[0].right = &tree[2];
    tree[1].val = 3;
    tree[1].left = &tree[3];
    tree[1].right = NULL;
    tree[2].val = 5;
    tree[2].left = NULL;
    tree[2].right = NULL;
    tree[3].val = 2;
    tree[3].left = NULL;
    tree[3].right = NULL;

    InOrderTraverse(&tree[0]);

    Solution so;
    so.ConvertByStack(&tree[0]);
}