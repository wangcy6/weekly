#include <iostream>
#include "c0514.h"

using namespace std;

int main()
{
	StackOfInt handle;

	handle.initialize(12);

	for(int i = 0; i < 12; i++)
	{
		handle.add(i + 100);
	}

	for(int i  = 0; i < 12;i++)
	{
		cout<<"handle["<<i<<"] = "<<handle.fetch(i)<<endl;
	}

	for(int i = 0 ; i < 12; i++)
	{
		handle.set(i, i + 1000);
		cout<<"handle["<<i<<"] = "<<handle.fetch(i)<<endl;
	}
	handle.add(1);
	handle.add(1);

}
