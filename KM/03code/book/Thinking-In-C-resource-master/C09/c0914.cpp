//先执行A的构造函数，再执行B的构造函数
#include <iostream>
class A {
	public:
	A()
	{
		std::cout<<"A()"<<std::endl;
		//class A;
	}
};

class B {
	A	m_a;
	public:
	B()
	{ 
		std::cout<<"B()"<<std::endl;
	}
};

int main(void)
{
	B	b;
	return 0;
}
