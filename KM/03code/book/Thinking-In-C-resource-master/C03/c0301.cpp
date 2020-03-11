
#include "c0301.h"

#include <iostream>

using namespace std;

void function1()
{
	cout<<"Function void;"<<endl;
}

/* char function2(char c, ...)
{
	cout<<"Function char;"<<endl;

	va_list ap;
	va_start(ap, c);

	for(char i = c; i != 'q'; i =va_arg(ap,char))
		cout<< i <<ends;
	cout<<endl;

	va_end(ap);

	return 'q';
} */

int function3(int i, ...)
{
	cout<<"Function int;"<<endl;
	va_list ap;
	va_start(ap, i);

	for(int j = i; j != 0; j = va_arg(ap,int))
		cout<< j <<ends;
	cout<<endl;

	va_end(ap);

	return 0;
}

float function4(float f, ...)
{
	cout<<"Function float;"<<endl;
	va_list ap;
	va_start(ap, f);

	for(float i = f; i != 0.0; i = va_arg(ap,float))
		cout<< i <<ends;
	cout<<endl;

	va_end(ap);

	return (float)1.0;
}
