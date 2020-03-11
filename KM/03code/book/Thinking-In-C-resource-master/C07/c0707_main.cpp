#include <iostream>
#include "c0707.h"

using namespace std;


int main()
{
	int a[] = {1,12,12,1,321564,564,1,321,23,132,132,13,21};
//	Stack intStack(a,sizeof a / sizeof *a);

	for(int i = 0; i < sizeof a / sizeof *a; i++)
	{
//		cout<<*(int*)intStack.pop()<<" ";
	}
}
