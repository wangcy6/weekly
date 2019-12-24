#include <iostream>

using namespace std;

struct structA{
struct structB{
	int mb_i;
	double mb_d;

	void initialize(int ival = 2, double dval = 2.2);
	void printf();
	void printfA();
};

int mb_i;
double mb_d;
int ma_i;
void initialize(int ival = 1, double dval = 1.1);
void printfA();
void printfB();
};

void structA::structB::initialize(int ival, double dval)
{
	mb_i = ival;
	mb_d  = dval;
}

void structA::initialize(int ival, double dval)
{
	mb_i = ival;
	mb_d = dval;
}
void structA::printfA()
{
	cout<<"sturctA mb_i = "<<mb_i<<endl
		<<"structA mb_d = "<<mb_d<<endl;
}
void structA::printfB()
{
	structB b;
	b.initialize();
	cout<<"structA::printfB() mb_i = "<<b.mb_i<<endl
		<<"structA::piintfB() mb_d = "<<b.mb_d<<endl;
}
void structA::structB::printf()
{
	cout<<"structB printf() mb_i = "<<mb_i<<endl
		<<"structB printf() mb_d = "<<mb_d<<endl;
}

void structA::structB::printfA()
{
	structA a;
	a.initialize(4,4.4);
	cout<<"structB::printfA() mb_i = "<<a.mb_i<<endl;
	cout<<"structB::printfA() mb_d = "<<a.mb_d<<endl;
}
int main()
{
	structA a;
	a.initialize();
	a.printfA();
	a.printfB();
	structA::structB b;
	b.initialize(3,3.3);
	b.printf();
	b.printfA();
}
