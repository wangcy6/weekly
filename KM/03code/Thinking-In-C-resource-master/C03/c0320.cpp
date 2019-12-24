#include <iostream>

using namespace std;
typedef struct
{
int i, j, k;
}ThreeDpoint;
int main()
{

ThreeDpoint Ls;

cout<<"sizeof(ThreeDpoint) =  "<<sizeof(ThreeDpoint)<<endl;

cout<<"&Ls.i = "<<(long)&Ls.i<<endl;
cout<<"&Ls.j = "<<(long)&Ls.j<<endl;
cout<<"&Ls.k = "<<(long)&Ls.k<<endl;


return 0;
}
