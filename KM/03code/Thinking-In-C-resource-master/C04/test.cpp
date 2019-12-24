#include <iostream>

using namespace std;
int main()
{
	int a = 0x12345678;

	char *chp = (char*)&a;

	chp++;
	chp += 3;
	cout<<*chp<<endl;
}


9
8
7
6
5
4
3
2
1
0
a

