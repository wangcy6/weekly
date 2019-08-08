#include<iostream>  
  
using namespace std; 
  
int main() 
{ 
   
    cout<<"Hello World"; 
      
    return 0; 
} 

/**

https://www.zhihu.com/question/21440194/answer/18237424
https://www.zhihu.com/question/52165135/answer/129287387


Linux X86 程序启动 – main函数是如何被执行的？
https://www.jianshu.com/p/eb39eac9d82e
https://luomuxiaoxiao.com/?p=516
shell 执行过程
内功修炼：程序是如何运行起来的
https://www.jianshu.com/p/7d11045a40f8
http://zhongmingmao.me/2019/04/13/linux-kernel-init/

在 linux 层面，线程的创建实际上是调用 clone 函数
nux中，可以使用一个进程来创建另外一个进程。这样的话，Linux的进程的组织结构其实有点像Linux目录树，是个层次结构的,可以使用 pstree命令来查看。在最
在Linux中创建一个新进程的方法是使用fork函数
***/