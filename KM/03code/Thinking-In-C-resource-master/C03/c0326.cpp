#include <iostream>

using namespace std;

void print(void* vp,int byte, unsigned char val)
{

for(int i = 0; i < byte;i++)
{
(static_cast<unsigned char*>(vp))[i] = val;
cout<<static_cast<unsigned char*>(vp)[i]<<endl;
}

}

int main()
{
int a[10];

int iInput;
int iVal;
void* iAptr = static_cast<void*> (a);
cout<<"Please input the range:";
cin>>iInput>>iVal;
cout<<endl;

print(iAptr,iInput,iVal);


return 0;
}
