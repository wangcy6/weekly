#include <iostream>

using namespace std;

void doubleFunc(const int size, double *dPtr)
{
for(int i = 0 ; i < size; i++)
{
cout<<dPtr[i]<<" "<<endl;
}
}

const int sz = 10;

int main()
{
double ArrayA[sz] = {0};

doubleFunc(sizeof(ArrayA)/sizeof(double),ArrayA);

unsigned char* uPtr = reinterpret_cast<unsigned char*>(ArrayA);
//注意i的上限计算
for(unsigned char* i = uPtr; i < uPtr + sizeof(ArrayA); i++)
{
*i = 1;
}

doubleFunc(sizeof(ArrayA)/sizeof(double),reinterpret_cast<double*>(uPtr));
doubleFunc(sizeof(ArrayA)/sizeof(double),ArrayA);

//doubleFunc(sizeof(ArrayA)/sizeof(double),uPtr);


return 0;
}
