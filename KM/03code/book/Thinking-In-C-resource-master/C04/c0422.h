#include <iostream>
#include "c0408.h"
#include <fstream>
#include "c0407.h"
#include <string>

using namespace std;
int main()
{
	ifstream in("test.cpp");
	Stack stack_Stash;
	Stash fileStash;

	stack_Stash.initialize();
	fileStash.initialize(sizeof(char));

	string line;
	for(int i = 0; i < 5; i++)
	{
		getline(in,line);
		cout<<line<<endl;

	}

}
