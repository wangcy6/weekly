#include <iostream>
#include <fstream>
#include <string>

#include "c0408.h"
#include "c0407.h"

using namespace std;

int main()
{
	ifstream in("test.cpp");

// creat a stack to save stash.
	Stack stack_Stash;
	stack_Stash.initialize();

	Stash* p = new Stash[20];
// Loading File ,every 5 rows to creat a Stash.
	string line;
	for(int i = 0 ; i < 20; i++)
	{
		p[i].initialize(sizeof(char));
	}

	int stashNumber = 0, lineNumber = 1;

	while(getline(in,line))
	{
		for(int i = 0; i < line.size(); i++)
		{
			p[stashNumber].add((void*)&line[i]);
		}
//
		char e = '\n';
		p[stashNumber].add((void*)&e);
		lineNumber++;
		if(lineNumber % 5 == 0)
			stashNumber++;
	}

// Push Stash into Stack.
	for(int i = 0; i <= stashNumber; i++)
	{
		stack_Stash.push((void*)(&p[i]));
	}

// stack.pop() and printf the file
// Document is not printf in reverse order.Becasue
// when we load the file. every 5 eow to creat a Stash.
// pop of the stack ,it was in reverse order.
	Stash* s;
	while((s = (Stash*)stack_Stash.pop()) != 0)
	{
		for(int j = 0; j < s->count(); j++)
		{
			cout<<*(char*)(s->fetch(j));
		}
	}
}
