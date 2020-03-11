#include <iostream>

using namespace std;

class Simple
{
	public:
	Simple();
	~Simple();
};

Simple::Simple()
{
	cout<<"Simple()::Simple()"<<endl;
}

Simple::~Simple()
{
	cout<<"release Simple"<<endl;
}

int main()
{

	Simple s;

}
