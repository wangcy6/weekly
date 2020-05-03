#include <iostream>
#include <string>

using namespace std;

void ChangeByPtr(string* sval)
{
cout<<"ChangeByPtr\nBefore Change："<<*sval<<endl;
*sval = "Change By Pointer!";
cout<<"after change: "<<*sval<<endl;
}

void ChangeByReference(string& sval)
{
cout<<"ChangeByReference\nBefore Change："<<sval<<endl;
sval = "Change By Reference!";
cout<<"after change: "<<sval<<endl;
}


int main()
{
string sInput;
cout<<"Please input a string:";
cin>>sInput;

ChangeByPtr(&sInput);
ChangeByReference(sInput);

return 0;
}
