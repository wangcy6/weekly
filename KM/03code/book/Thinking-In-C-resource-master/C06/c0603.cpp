#include <iostream>

using namespace std;

class Simple
{
	int i;
	public:
	Simple(int val);
	~Simple();
};

Simple::Simple(int val)
{
	i = val;
	cout<<"Simple()::Simple()  i = "<<i<<endl;
}

Simple::~Simple()
{
	cout<<"release Simple  i = "<<i<<endl;
}

int main()
{

	Simple s(10);
}
