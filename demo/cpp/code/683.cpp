#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector> 
#include <climits>
using namespace std;

   class Solution
    {
    public:
        /**
     * @param flowers: the place where the flower will open in that day 每天只开一朵花，which天which盆花会开放。
     * @param k:  an integer 开花的间距
     * @return: in which day meet the requirements
     */
        int kEmptySlots(vector<int> &flowers, int k)
        {
            // Write your code here
            int n = flowers.size();
            if (k >= n || n == 0)
                return -1;
            vector<int> position(n + 1, 0);
            //flowers: day --positon
            //position:  positon --day
            //day 从 0开始，position从1开始
            //不断循环判断
            for (int i = 0; i < n; i++)
            {
                position[flowers[i]] = i; //
            }

            int start = 1;       // start 开花位置
            int end = 1 + k + 1; //end 开花位置 k=end-start
            int res = INT_MAX;
            cout<< "start="<<start <<" end="<<end<<endl;
            //position 下标是从1开始的，代表第一盆花
            for (int i = 1; i < n + 1; ++i)
            {
                //如何证明[start end] 之间内没有花开 
                //观察规律 晚开的花在[start,end]中间部分，属于符合要求的
                //else
                //如果发生在start  end 边界上 需要重新移动窗口
                //观察规律 才能让晚开的花在[start,end] ,
                if (position[i] > position[start] && position[i] > position[end])
                {   
                     cout<<"====i=" <<i <<" start="<<start <<" end="<<end<<endl;
                    continue;
                }
                if (i == end)
                {   
                    cout<<" i=" <<i<<" i == end start="<<start <<" end="<<end<<endl;
                    res = min(res, max(position[start], position[end]) + 1);
                }

                //变化

                cout<<" i=" <<i<< "11  start="<<start <<" end="<<end<<endl;
                start = i;
                end = i + k + 1;
                cout<<" i=" << "22  start="<<start <<" end="<<end<<endl;
            }
            return res == INT_MAX ? -1 : res;
        }
    };
//g++  -std=c++11 683.cpp 
int main()
{
   Solution test;
  vector<int> data={1,2,3,4};
//vector<int> data={1,3,2};
   cout<<""<<endl;
   cout<<test.kEmptySlots(data,1);
  cout<<""<<endl;
   return 0;
}