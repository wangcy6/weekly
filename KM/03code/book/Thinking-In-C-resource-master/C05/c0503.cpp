#include <iostream>

using namespace std;

class CFriend
{
	int i;
	char c;
	friend void global(CFriend* x, int i, char c);
};

void global(CFriend* x, int i, char c)
{
	x->i = i;
	x->c = c;
	cout<<"x.i = "<<x->i<<endl;
	cout<<"x.c = "<<x->c<<endl;
}

int main()
{
	CFriend f;

	global(&f, 1, 'a');
}
