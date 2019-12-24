#include <iostream>

using namespace std;


union Packed{
char   c; 
//short  s;
//int    i;
//double d;
//float  f;
//long   l;
};



int main()
{
cout<<"sizeof(long)   = "<<sizeof(long)<<endl;
cout<<"sizeof(float)  = "<<sizeof(float)<<endl;
cout<<"sizeof(double) = "<<sizeof(double)<<endl;
cout<<"sizeof(int)    = "<<sizeof(int)<<endl;

cout<<"sizeof(Packed) = "<<sizeof(Packed)<<endl;
//删除不同的元素对union造成的影响
//sizeof(long)根据具体操作系统和编译平台大小不同
//笔者的是64位ubuntn 14.04LTS GNU 编译器 4.8.2 故sizeof(long) = 8;
return 0;
}
