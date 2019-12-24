#include <iostream>

using namespace std;

char* func(char* cptr, int size)
{
	char * p = new char[size];
	for(int i = 0; i < size; i++)
	{
		p[i] = cptr[i];
	}
	return p;
}


int main()
{
	char string[] ={"hello Mylady lsy!!"};
	char* p  = func(string,sizeof(string));
	cout<<string<<endl;
	cout<<(long)string<<endl;
	cout<<p<<endl;
	cout<<(long)p<<endl;
	delete []p;
}
