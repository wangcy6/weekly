#include <iostream>

using namespace std;

class Simple
{
	int i;
	public:
	Simple(int val);
	void print();
	~Simple();
};

Simple::Simple(int val)
{
	i = val;
	cout<<"Simple()::Simple()  i = "<<i<<endl;
}
void Simple::print()
{
	cout<<"i = "<< i<<endl;
}

Simple::~Simple()
{
	cout<<"release Simple  i = "<<i<<endl;
}

int main()
{
	
	Simple s[] = {Simple(1), Simple(2), Simple(3), Simple(4)};

	for(int i = 0; i < (sizeof s / sizeof *s); i++)
	  s[i].print();
}
