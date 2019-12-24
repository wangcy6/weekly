#include <iostream>

using namespace std;

class Simple{
	public:
	Simple(void);
};

Simple::Simple(void)
{
	cout<<"Simple()::Simple()"<<endl;
}

int
main(void)
{
	Simple s;
	return (0);
}
