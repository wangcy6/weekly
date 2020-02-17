#include <iostream>

using namespace std;


int main()
{
	int i;
	for(i = 0; i < 10; i++)
	{
		cout<<"i = "<<i<<endl;
	}

	for(int i = 0; i < 10; i++)
	{
		cout<<"i2 = "<<i<<endl;
		//局部变量会屏蔽其封闭块内的其他同名变量
	}
}
