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
	int i = 0;
	while(1)
	{
		Simple s(10);
		i++;
		if(10 == i)
		  goto a;
	}
a: cout<<"Goto Here"<<endl;
}

// 有问题!!!!
