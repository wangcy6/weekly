#include <iostream>

#include "c0407.h"

int main()
{
Stash d;
d.initialize(sizeof(double));

for(int i = 0; i != 25; i++)
{
double j = i * 1.11;
d.add(&j);
}

for(int i = 0; i < d.count(); i++)
{
std::cout<<"doubleStash.fetch("<<i<<") = "
<<*(double*)d.fetch(i)
<<std::endl;
}

d.cleanup();

return 0;
}
