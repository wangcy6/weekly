#include <iostream>

#define DEBUG
int main()
{
#ifdef DEBUG
	std::cout<<"DEBUG!!"<<std::endl;
#endif// DEBUG
#ifndef DEBUG
	std::cout<<"NO DEBUG!!"<<std::endl;
#endif
	return 0;
}
