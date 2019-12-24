#include <iostream>

using namespace std;

int main()
{
const 	 double cdA[10] = {1.0};
volatile double vdA[10] = {0.0};


for(int i = 0; i < 10; i++)
{
double *j = const_cast<double*>(&cdA[i]);
*j = i * 1.1;
cout<<cdA[i]<<" ";
double *k = const_cast<double*>(&vdA[i]);
*k = i * 2.2;
cout<<vdA[i]<<endl;
}
return 0;
}
