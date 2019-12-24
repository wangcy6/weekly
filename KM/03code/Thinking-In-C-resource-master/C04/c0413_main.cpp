#include <iostream>
#include "c0408.h"
#include "c0413.h"
#include <cstdlib>

using namespace std;


int main()
{
	CVideo lsyVideo[3];
	Stack videoStack;
	for(int i = 1; i < 4; i++)
	{
		lsyVideo[i - 1].initialize(i, i * 3, i * 1024,
					20150327 , 20150330, 6, "MyLady");
		videoStack.push((void*)&lsyVideo[i - 1]);
	}
	for(int i = 0; i < 3; i++)
	{
		lsyVideo[i].printf();
		((CVideo*)videoStack.pop())->printf();
	}
}
