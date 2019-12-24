#include <iostream>
#include <string>

using namespace std;

class myClass
{
int m_i;

public:
void myFunc(int ival);
void printf(string str, int val);
};

void myClass::myFunc(int ival)
{
this->m_i = ival;
std::cout<<"m_i"<<this->m_i<<std::endl;
std::cout<<"ival + 3 = "<<ival + 3<<std::endl;

this->printf("m_i",this->m_i);
this->printf("ival + 3",ival + 3);
}

void myClass::printf(string str, int val)
{
cout<<str<<val<<endl;
}

int main()
{

myClass my;

my.myFunc(2);
my.myFunc(3);

return 0;
}

