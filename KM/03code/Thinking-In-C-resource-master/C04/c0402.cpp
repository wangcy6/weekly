#include <iostream>

struct Forzen
{
void Func();
};


void Forzen::Func()
{
std::cout<<"Frozen Func();"<<std::endl;
}

int main()
{
Forzen myForzen;

myForzen.Func();

return 0;
}
