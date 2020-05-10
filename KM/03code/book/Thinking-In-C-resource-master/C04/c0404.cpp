#include <iostream>

struct Heart
{
int m_i;
};

void Func1(Heart* val)
{
int i;
i = val->m_i;
std::cout<<"Func1() i = "<<i<<std::endl;
}

void Func2(Heart* val)
{
std::cout<<"Func2() Heart m_i = "<<val->m_i<<std::endl;
}

int main()
{
Heart myHeart;
myHeart.m_i = 1;

Func1(&myHeart);
Func2(&myHeart);

return 0;
}
