#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

class Base{
	public:
		int f() const {
			cout<<"Bae::f() \n";
			return 1;
		};
		int f(string) const 
		{
			return 1;
		}

		void g() {}

		double h() const{
			cout<<"Base::h()\n";
			return 2.0;
		}
		double h(double) const{
			return 3.0;
		}

		double h(int) const{
			return 4.0;
		}
};

class Derived1: public Base {
	public:
		void g() const {}
};

class Derived2: public Base {
	public:
		int f() const {
			cout<< "Derived2::f() \n";
			return 2;
		}
};

class Derived3: public Base {
	public:
		void f() const{
			cout<<"Derived3::f() \n";
		}
};

class Derived4: public Base{
	public:
		int f(int) const {
			cout<<"Derived4::f() \n";
			return 4;
		}
};

class Derived5: public Base{
	public:
		int h(int) const{
			cout<<"Derived5::h(int) \n";
			return 5;
		}
};

int main()
{
	string s("hello");

	Derived1 d1;

	int x = d1.f();
	d1.f(s);

	Derived2 d2;
	x = d2.f();
	//error: no matching function for call to ‘Derived2::f(std::string&)’
	//d2.f(s);

	Derived3 d3;
	d3.f();
	//x = d3.f(); error: void value not ignored as it ought to be

	Derived4 d4;
	//x = d4.f(); error: no matching function for call to ‘Derived4::f()’
	x = d4.f(1);

	Derived5 d5;
	d5.h(1);
	//d5.h(); error: no matching function for call to ‘Derived5::h()’


}

