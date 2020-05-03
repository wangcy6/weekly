#include <iostream>

using namespace std;
int main()
{
int a[10];
void* b = (void*)((void*)&a[9] + 4);
//char c;
//int b[10];

for(int i = 0 ; i <  10; i++)
cout<<"&a["<<i<<"]"<<(long)&a[i]<<endl;
//cout<<(long)&c<<endl;
//for(int i = 0 ; i <  10; i++)
//cout<<"&b["<<i<<"]"<<(long)&b[i]<<endl;

return 0;
}


