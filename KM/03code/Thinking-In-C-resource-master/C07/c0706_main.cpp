#include <iostream>
#include "c0706.h"

using namespace std;


int main()
{
	Stash s(sizeof(char), 200);
	Stash s2(sizeof(int));

	for(int i = 0; i < 100; i++)
	{
		s2.add(&i);
	}

	for(int i = 0; i < s2.count(); i++)
	{
		cout<<*(int*)s2.fetch(i)<<" ";
	}
	for(char a = 'a'; a < 'z'; a++)
	{
		s.add(&a);
	}
	for(int i = 0; i < s.count(); i++)
	{
		cout<<*(char*)s.fetch(i)<<" ";
	}

}
