#include <iostream>

int main()
{
	int* ival = new int;
	long* lval = new long;
	char* a = new char[100];

	std::cout<<"(long)& ival = "<<(long)ival<<std::endl
		    <<"(long)&lval = "<<(long)lval<<std::endl
			<<"(long)&a    = "<<(long)a<<std::endl;

	delete ival;
	delete lval;
	delete []a;
	return 0;
}
