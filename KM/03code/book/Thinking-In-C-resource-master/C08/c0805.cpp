#include <stdlib.h>
#include <iostream>
#include <ctime>

using namespace std;

int
main(void)
{
	time_t	currentTime;
	const time_t	firstTime = time(&currentTime);

	time(&currentTime);

	//firstTime = currentTime;
	//只读，常量一旦被赋值就不能被修改了.
	return 0;	
}
