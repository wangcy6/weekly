#include <iostream>
#include "c0312.h"

using namespace std;

#define PR(STR,EXPR) cout<<STR; printBinary(EXPR); cout << endl;

int main()
{
unsigned int uigetval;
unsigned char a, b;
cout<<"Enter a number between 0 and 255:";
cin>>uigetval;
a = uigetval;
cout<<"Enter a number betwenn 0 and 255:";
cin>>uigetval;
b = uigetval;

PR("a in binary: ",a);
PR("b in binary: ",b);

PR("a | b =      ",a or b);
PR("a & b =      ",a and b);
PR("a ^ b =      ",a xor b);
PR("~a    =      ",compl a);
PR("~b    =      ",compl b);

//An interesting bit pattern:
unsigned char c = 0x5A;

PR("c in binary: ",c);
a |= c;
PR("a |= c; a=   ",a);
b |= c;
PR("b |= c; b =  ",b);
b &= c;
PR("b &= c; b =  ",b);
b ^= a;
PR("b ^= a; b =  ",b);



return 0;
}

