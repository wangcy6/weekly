#include <iostream>

using namespace std;
double d[] = {
	1.1, 1.2, 1.3, 1.4, 1.5
};

int main()
{
	double* const cptr = d;
	cout<<"d  = "<<*cptr<<" cdptr = "<<(long)cptr<<endl;

	//指针常量, 可修改指针指向的内容，但是不能修改指针本身
	*cptr = 2.0f;

	double dother = 2.0f;
	//cdptr = &dother;
	//c0809.cpp:14:8: error: assignment of read-only variable ‘cdptr’
	//	  cdptr = &dother;//Error
	cout<<"d  = "<<*cptr<<"   cdptr = "<<(long)cptr<<endl;
	
	return 0;
}
