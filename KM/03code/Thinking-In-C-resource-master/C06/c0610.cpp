#include <iostream>

using namespace std;

class CNoConstructor{
	public:
	CNoConstructor(int i);
};

CNoConstructor::CNoConstructor(int i)
{}

int
main(void)
{
	//Wrong  一旦有了一个构造函数，编译器就会确保不管在什么情况下它总会被调用。当且仅当在一个结构（struct 或者Class）
	//没有构造函数时，编译器就会自动为它创建一个。
	//CNoConstructor c;
	CNoConstructor c(10);
	exit(0);
}
