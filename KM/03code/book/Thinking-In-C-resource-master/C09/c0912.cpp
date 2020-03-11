#include "c0912.h"
#include <iostream>

int main(void)
{
	Time	start;
	std::cin.get();
	Time	end;
	std::cout<<std::endl;
	std::cout<<"start = "<<start.ascii()<<std::endl;
	std::cout<<"end = "<<end.ascii()<<std::endl;
	std::cout<<"delta = "<<end.delta(&start)<<std::endl;
	return 0;
}
