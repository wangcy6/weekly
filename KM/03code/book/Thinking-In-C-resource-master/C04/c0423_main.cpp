#include <iostream>
#include "c0423.h"

using namespace std;
int main()
{
	StackSth s;

	s.initialize("test.cpp");

	for(int i = 0 ; i < 6; i++)
	{
	s.addLine();
	}
	for(int i = 0; i < 19; i++)
	{
		s.fetch(i);
	}
}

