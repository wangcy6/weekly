#include <iostream>
#include "c0606.h"

using namespace std;

int main()
{
	Handle u;

	cout<<"u = "<<u.read()<<endl;
	u.change(10);
	cout<<"u = "<<u.read()<<endl;

}
