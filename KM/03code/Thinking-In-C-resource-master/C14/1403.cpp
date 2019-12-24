#include <iostream>

using namespace std;

class Base{
	public:
		Base() {cout<<"Base constructor\n";}
		~Base() {cout<<"Base destructor\n";}
};

class Derived : public Base{
	public:
		Derived() {cout<<"Derived constructor\n";}
		~Derived() {cout<<"Derived destructor\n";}
};


class Derived2 : public Derived{
	public:
		Derived2() {cout<<"Derived2 constructor\n";}
		~Derived2() {cout<<"Derived2 destructor\n";}
};

int main()
{
	Derived2 d2;
}

//output:
//Base constructor
//Derived constructor
//Derived2 constructor
//Derived2 destructor
//Derived destructor
//Base destructor
//构造是从类层次的最根处开始

