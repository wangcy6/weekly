//要证明inline为内联函数，只要在一个文件作用域内定义他
//然后将此文件与另外一个文件一起进行编译，链接，在另外
//一个文件里用extern来声明要使用的函数，若能够找到内联
//函数的定义，则说明内联函数不是内部连接，反之则是．
#include <iostream>

extern int f2();//声明一个外部连接函数
extern int f1();
//在c0906_1.cpp进行该函数的定义
//编译并连接２个文件
//g++ c0906_1.cpp c0906.cpp
//连接时出现如下错误
//c0906.cpp:(.text+0x5): undefined reference to `f2()'
//collect2: error: ld returned 1 exit status
//说明找不到内联函数f2的定义．
int main(void)
{
	//链接时会出现错误
	//std::cout<<f2()<<std::endl;
	//f1为非内联函数，故能够找到其定义
	std::cout<<f1()<<std::endl;

	return 0;
}
