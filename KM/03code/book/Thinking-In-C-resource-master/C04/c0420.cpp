#include <iostream>

using namespace std;

struct data
{
	short s;
	int i;
	char c;

};

struct dataAndFunc
{
	int i;
	char c;
	double d;
	char e;
	void printf()
	{
		std::cout<<"i = "<<i<<endl
			<<"c = "<<endl
			<<"d = "<<endl;
	}
};
struct empty{};
//In C++, empty structures are part of the language. G++ treats empty structures as if they had a single member of type char.
//在C++下，空类和空结构体的大小是1（编译器相关），这是为什么呢？为什么不是0？
//这是因为，C++标准中规定，“no object shall have the same address in memory as any other variable” ，就是任何不同的对象不能拥有相同的内存地址。 如果空类大小为0，若我们声明一个这个类的对象数组，那么数组中的每个对象都拥有了相同的地址，这显然是违背标准的。
//在C++中，对象就是变量，它的最纯正的定义是“一块存储区”（更确切的说法是，对象必须有唯一的标志），在C++中是一个唯一的地址。
int main()
{
	std::cout<<"sizeof data ="<<sizeof(data)<<std::endl;
	std::cout<<"sizeof dataAndFUnc = "<<sizeof(dataAndFunc)<<std::endl;
	std::cout<<"sizeof empty = "<<sizeof(empty)<<std::endl;
	return 0;
}
