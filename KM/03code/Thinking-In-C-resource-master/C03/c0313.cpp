#include <iostream>
#include "c0312.h"

using namespace std;
#define PR(STR,EXPR) cout << STR; printBinary(EXPR); cout << endl;
unsigned char rol(unsigned char val)
{
int highbit;
if(val & 0x80)
{
highbit =  1;
}
else
{
highbit = 0;
}
val <<= 1;
val |= highbit;
return val;
}
unsigned char ror(unsigned char val)
{
int lowbit;
if(val & 1)
{
lowbit = 1;
}
else
{
lowbit = 0;
}
val >>= 1;
val |= (lowbit<<7);//注意下
return val;
}

int main(int argc, char *argv[])
{

unsigned int iGetval, iCount;
cout<<"Enter a number and n:";
cin>>iGetval>>iCount;
unsigned char cInput = iGetval;
PR("Begin: ",cInput);
for(int i = 0 ; i != iCount; i++)
{
cInput = rol(cInput);
PR("       ",cInput);
}
for(int j = 0 ; j != iCount;j++)
{
cInput = ror(cInput);
PR("       ",cInput);
}

return 0;
}
