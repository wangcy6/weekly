#include <iostream>
#include "c0416.h"

int main()
{
	VStash doubleStash;
	doubleStash.initialize(sizeof(double));

	for(int i = 0 ; i < 10; i++)
	{
		double j = i * 1.1;
		doubleStash.add((void*)&j);
	}

	for(int i = 0; i < 10; i++)
	{
		std::cout<<"doubleStash "<<i<<" = "
			<<*(double*)doubleStash.fetch(i)
			<<std::endl;
	}
}
