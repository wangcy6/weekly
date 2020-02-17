class A{
	int i;
	public:
	A(int ii): i(ii){}
	~A() {}
	void f() const {}
};

class B{
	int i;
	public:
	B(int ii): i(i){}
	~B(){}
	void f()const {}
};

class C : public B{
	A a;
	public:
	C(int ii):B(ii), a(ii) {}
	~C() {}
	void f() const {
		a.f();
		B::f();
	}
};

int main()
{
	C c(47);
}
