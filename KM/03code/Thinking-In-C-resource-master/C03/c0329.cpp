#include <cstdlib>
#include <iostream>

using namespace std;

void printfBinary(const unsigned char val)
{
for(int i = 7 ; i >= 0; i--)
{
if(val&(i>>1))
cout<<1;
else
cout<<0;
}
cout<<endl;
}

int main(int argc, char* argv[])
{
if(argc != 2)
{
cout << "Must provide a number" << endl;
exit(1);
}

double d = atof(argv[1]);

unsigned char * cp = 
reinterpret_cast<unsigned char*>(&d);
for(int i = sizeof(double); i > 0; i -= 2)
{
printfBinary(cp[i - 1]);
printfBinary(cp[i]);
}


return 0;
}
