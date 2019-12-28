#include "malloc.h"
#include <iostream>
#include <new>
using namespace std;

#define MAX_LEN 1024*1024*10 //10M

void get_malloc_size(void* p,int i) {
  size_t size = malloc_usable_size(p);
  std::cout <<"i="<<i << " heap malloc size is: " << size << '\n';
}
/****
 * 1 测试1 栈上申请对象是否多申请 --no
 * 2.测试2 堆上申请是否多申请 --yes
 *****/ 
int main() {
  
  //int big[MAX_LEN];//Segmentation Fault
  std::cout <<"MAX_LEN="<<MAX_LEN << " stack malloc size is: " << sizeof(int) << '\n';
  for (int i=0;i<100;i++)
  {
    char* p = new(std::nothrow) char[i]; //min(24,24+n*16)
    if (p ==0)
    {
        std::cout <<"i="<<i << " new failed "  << '\n';
        return -1;//bad_alloc
    }
    char array[i];
    get_malloc_size(p,i);
    std::cout <<"i="<<i << " stack malloc size is: " << sizeof(array) << '\n';

  }
  return 0;
}


/**
 * Linux环境下段错误的产生原因及调试方法小结
 * 栈溢出
 * 访问只读的内存地址
 * 访问系统保护的内存地址 越界
 * 访问不存在的内存地址
 *  0000000000400a24 sp 00007ffd77d5eef0 error
 * SP寄存器为堆栈指针，SP始终指向栈顶
 * int big[MAX_LEN];//Segmentation Fault
 * https://www.cnblogs.com/panfeng412/archive/2011/11/06/segmentation-fault-in-linux.html
 * dmesg
 * nm
 * -g
 * dmesg可以在应用程序crash掉时，显示内核中保存的相关信息。如下所示，通过dmesg命令可以查看发生段错误的程序名称、引起段错误发生的内存地址、指令指针地址、堆栈指针地址、错误代码、错误原因
 * ldd
 * 4.4.2 适用场景
    1、不需要-g参数编译，不需要借助于core文件，但需要有一定的汇编语言基础。
    2、如果使用了gcc编译优化参数（-O1，-O2，-O3）的话，生成的汇编指令将会被优化，使得调试过程有些难度
    Segmentation fault  不是c++异常。
    https://dins.site/coding-std-exception-chs/

    抛出异常
    http://www.cplusplus.com/reference/new/bad_alloc/
    https://en.wikipedia.org/wiki/Segmentation_fault
 */

/**
 * 其他
 * operator new
 * http://www.cplusplus.com/reference/new/operator%20new/
 * throwing (1)	
    void* operator new (std::size_t size);
    nothrow (2)	
    void* operator new (std::size_t size, const std::nothrow_t& nothrow_value) noexcept
 * https://www.cnblogs.com/lyq105/archive/2009/11/28/1612678.html
 * 
 * i=95 heap malloc size is: 104
    i=95 stack malloc size is: 95
    i=96 heap malloc size is: 104
    i=96 stack malloc size is: 96
    i=97 heap malloc size is: 104
    i=97 stack malloc size is: 97
    i=98 heap malloc size is: 104
    i=98 stack malloc size is: 98
    i=99 heap malloc size is: 104
    i=99 stack malloc size is: 99
    */


   //https://www.runoob.com/cplusplus/cpp-exceptions-handling.html
   //echo $? 139
