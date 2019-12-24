#include <iostream>
using namespace std;
class A{
	public:
	A() { cout<<"A() constructor\n"; }
	~A() { cout<<"~A() destructor\n"; }
};

class B{
	public:
	B() { cout<<"B() constructor\n"; }
	~B() { cout<<"~B() destructor\n"; }
};

class C: public A{
	public:
		B b;
};

int main()
{
	C c;
}
//结果:构造是从类层次的最根处开始,而在每一层,首先会调用基类构造函数,
//然后调用成员对象构造函数.调用析构函数严格按照构造函数相反的次序.

//output:
//A() constructor
//B() constructor
//~B() destructor
//~A() destructor
