#include <iostream>
using namespace std;

class A{
	int i;
	public:
	A(int ii): i(ii){ cout<<"A() constructor\n";}
	~A() {cout<<"~A() destructor\n";}
	void f() const {}
};

class B{
	int i;
	public:
	B(int ii): i(i){ cout<<"B() constructor\n";}
	~B(){ cout<<"~B() destructor\n"; }
	void f()const {}
};

class C : public B{
	A a;
	public:
	C(int ii):B(ii), a(ii) { cout<<"C() constructor\n";}
	~C() { cout<<"~C() destructor\n"; }
	void f() const {
		a.f();
		B::f();
	}
};

class D: public B{
	C c;
	public:
	D(int ii): B(ii),c(ii) { cout<<"D() constructor\n";}
	~D(){ cout<<"~D() destructor\n"; }
};
int main()
{
	D d(50);
}
