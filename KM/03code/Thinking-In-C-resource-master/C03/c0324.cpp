#include <iostream>

using namespace std;

#define P(EX)  cout<<#EX<<":"<<EX<<endl;


int main()
{
long lA[10];
long double ldA[10];


for(long i = 0; i < 10; i++)
{
lA[i] = i * 10;
ldA[i] = i * 100;
}


long *lPtr = lA;


P(*lPtr);

P(*++lPtr);

P(*(lPtr + 5));

long *lPtr2 = lPtr + 5;

P(*lPtr2);
P(*(lPtr2 - 4));
P(*(--lPtr2));

long double *ldPtr = ldA;

P(*ldPtr);

P(*++ldPtr);

P(*(ldPtr + 5));

long double *ldPtr2 = ldPtr + 5;

P(*ldPtr2);
P(*(ldPtr2 - 4));
P(*(--ldPtr2));
 
return 0;
}
