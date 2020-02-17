#include <iostream>

using namespace std;
//要让BAND宏能够正常工作就是将其改为函数形式
//为了保持效率，也可改为内联函数的形式

inline int Band(int x, int b)
{
	return (x >= b ? 1 : 0);
}

int main(void)
{
	int a = 10, b = 11;
	if (Band(a++, b))
		cout << "a > b" <<endl;
	else
		cout << "a <= b" <<endl;
	return 0;
}
