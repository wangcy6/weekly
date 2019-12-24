#include <iostream>
#include <string>

using namespace std;

typedef struct
{
string m_string1;
string m_string2;
int m_int;
} MySy;


int main()
{
MySy m;

m.m_string1 = "First String.";
m.m_string2 = "Second String.";
m.m_int = 1997;

cout<<"m_string1: "<<m.m_string1<<endl;
cout<<"m_string2: "<<m.m_string2<<endl;
cout<<"m_int:     "<<m.m_int    <<endl;

MySy* mPtr = &m;

mPtr->m_string1 = "Change Successful1!";
mPtr->m_string2 = "Change Successful2!";
mPtr->m_int = 7991;

cout<<"Final m_String1 "<<mPtr->m_string1<<endl;
cout<<"Final m_string2 "<<mPtr->m_string2<<endl;
cout<<"Final m_int     "<<mPtr->m_int<<endl;
return 0;
}

