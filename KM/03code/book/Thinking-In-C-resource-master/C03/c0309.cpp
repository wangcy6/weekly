#include <iostream>

using namespace std;

void func()
{
//static int i = 0; 解释 去掉static之后i变成局部变量 函数执行完之后 系统不再分配内存
int i = 0;
cout<<"i = "<<++i<<" "<<(long)&i<<endl;
}


int main()
{
for(int x= 0; x < 10; x++)
func();


return 0;
}


