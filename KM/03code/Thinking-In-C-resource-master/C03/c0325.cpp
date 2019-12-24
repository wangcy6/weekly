#include <iostream>


void printBinary(const unsigned char val)
{
for(int i = 7; i >= 0; i--)
{
if(val& (1<<i))
std::cout<<1;
else
std::cout<<0;
}
}

int main()
{
float f = 1.0;

unsigned char * fPtr = (unsigned char*)&f;

for(int i = 0; i < sizeof(float); ++i)
{
printBinary(fPtr[i]);
std::cout<<" ";
}
std::cout<<std::endl;



return 0;
}
