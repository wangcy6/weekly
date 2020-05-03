/*
 *c++语言规定，只有在类声明结束以后，内联函数
 *才会计算．也就是说，内联函数在使用未定义的成员
 *函数的时候，不需要前向声明.
 */
#include <iostream>

class Forward {
	public:
	void first()
	{
		second();
	}
	void second()
	{
		std::cout << "This is second function.\n";
	}
};

int main(void)
{
	Forward	f;
	f.first();
	return 0;
}
