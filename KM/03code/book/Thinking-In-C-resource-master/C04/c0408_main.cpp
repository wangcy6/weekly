#include <iostream>
#include "c0408.h"

using namespace std;

int main()
{
Stack doubleStack;
double j[25];
for(int i = 0 ; i != 25; i++)
{
j[i] = i * 1.1;
doubleStack.push((void*)&(j[i]));
cout<<*(double*)doubleStack.peek()<<endl;
}

for(int i = 0 ; i != 25; i++)
{
cout<<"doubleStack pop "<<i + 1<<" = "
<<*(double*)(doubleStack.pop())<<endl;
}

doubleStack.cleanup();
return 0;
}
