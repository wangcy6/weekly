#include <iostream>
#include <string>
#include "c0608.h"

using namespace std;

int main()
{
	string s[] = {"hello", "goodgirl", "see you!"};
	
	Stack sofs;
	for(int i = 0 ; i < 3; i++)
	sofs.push((void*)(&s[i]));
	
	string *tmp;
	while((tmp = (string*)sofs.pop()) != 0)
	  cout<<*tmp<<endl;
	
}
