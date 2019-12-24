#include <fstream>

using namespace std;

ofstream out("1406.out");

#define CLASS(ID) class ID {\
	public: \
		ID(int) {out <<#ID " constructor\n";}\
		~ID() { out<<#ID " destructor\n";} \
};

CLASS(Base1);
CLASS(Member1);
CLASS(Member2);
CLASS(Member3);
CLASS(Member4);
CLASS(Member5);

class Derived1: public Base1{
	Member1 m1;
	Member2 m2;
	public:
	Derived1(int): m2(1), m1(2), Base1(3){
		out<<"Derived1() constructor\n";
	}
	~Derived1()
	{
		out<<"~Derived1() destructor\n";
	}
};


class Derived2 :public Derived1{
	Member3 m3;
	Member4 m4;
	public:
	Derived2(): m3(1), Derived1(2), m4(3)
	{
		out<<"Derived2() construtor\n";
	}

	~Derived2()
	{
		out<<"~Derived2() destructor\n";
	}
};

class Derived3: public Derived2{
	Member4 m4;
	Member5 m5;
	public:
	Derived3(): m4(1), m5(2){
		out<<"Derived3() constructor\n";
	}
	~Derived3()
	{
		out<<"~Derived3() destructor\n";
	}
};

int main()
{
	Derived3 d3;
}
