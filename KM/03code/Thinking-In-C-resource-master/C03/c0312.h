#include <iostream>

void printBinary(int ival){
for(int i = 7; i >= 0; i--){
	if(ival & (1 << i))
	std::cout<<"1";
	else
	std::cout<<"0";
 }
}



