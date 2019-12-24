#include <iostream>

using namespace std;

class SuperVar {
	union {
		char c;
		int i;
		float f;
	};
	public:
	enum dataType 
	{
		character,
		integer,
		floating_point
	};
	SuperVar(char ch);
	SuperVar(int ii);
	SuperVar(float ff);
	~SuperVar();
	void print(dataType type);
};


SuperVar::SuperVar(char ch){
#ifdef DEBUG
	vartype = character;
#endif //DEBUG
	c = ch;
}
SuperVar::SuperVar(int ii){
#ifdef DEBUG
	vartype = integer;
#endif //DEBUG
	i = ii;
}
SuperVar::SuperVar(float ff){
#ifdef DEBUG
	vartype = floating_point;
#endif //DEBUG
	f = ff;
}
SuperVar::~SuperVar()
{}

void SuperVar::print(dataType type)
{
	switch (type)
	{
		case character:
			cout<<"character :"<< c <<endl;
			break;
		case integer:
			cout<<"interger :"<< i <<endl;
			break;
		case floating_point: 
			cout<<"floating_point : "<< f <<endl;
			break;
	}
}


int main()
{
	SuperVar A('a'),B(1),C(2.2F);
	SuperVar::dataType vartype;
	vartype = SuperVar::character;
	A.print(vartype);
	vartype = SuperVar::integer;
	B.print(vartype);
	vartype = SuperVar::floating_point;
	C.print(vartype);
}
