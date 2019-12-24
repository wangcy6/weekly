#include "iostream"
#include <typeinfo>
using namespace std;
/***
 * 一个典型的程序运行步骤
 *
   a.操作系统在创建进程后，把控制权交到了程序的入口，这个入口往往是运行库中的某个入口函数。(fork)
   b.入口函数对运行库和程序运行环境进行初始化，包括堆、I/O、线程、全局变量构造，等等。(exec)
   c. 入口函数在完成初始化之后，调用main函数，正式开始执行程序主体部分。
   d. main函数执行完毕以后，返回到入口函数，
     入口函数进行清理工作，包括全局变量析构、堆销毁、关闭I/O等，然后进行系统调用结束进程。

                1. 初始化和OS版本有关的全局变量。
                2. 初始化堆。
                3. 初始化I/O。
                4. 获取命令行参数和环境变量。
                5. 初始化C库的一些数据。
                6. 调用main并记录返回值。
                7. 检查错误并将main的返回值返回。

 *
 * C/C++程序的运行流程
 * Entry Point:
   1、全局变量/对象的构建，初始化。对于全局变量，没有给定初始化值的，初始化为0。对于全局对象，没有指定构造函数的，调用默认构造函数。 
 * 2、进入main函数
 * 3、退出main函数
 *   main 函数的返回值类型必须是 int ，
 * 这样返回值才能传递给程序的激活者（如操作
 统）。
 return 0; 返回给操作系统程序的执行状态为 0，表示正常退出
 * 4、全局变量对象的回收
 *
 * echo $?
 *
 *
 */
int a;
a = 3; // error: ‘a’ does not name a type
// main’ must return ‘int’
int main(int argc, char *argv[]) {
  return 0;
  cout << "main is over ,you can not wait  " << end;
}