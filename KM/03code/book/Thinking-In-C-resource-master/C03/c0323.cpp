#include <iostream>

using namespace std;

typedef union
{
char         c;
short        s;
long         l;
float 	     f;
double       d;
long double ld;
} Primitives;



int main()
{
Primitives p[10];
Primitives *pPtr = p;

cout<<"sizeof(Primitives) = "<<sizeof(Primitives)<<endl;
cout<<"pPtr  = "<<(long)pPtr<<endl;
++pPtr;
cout<<"pPtr  = "<<(long)pPtr<<endl;

return 0;
}
