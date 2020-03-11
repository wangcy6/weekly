#include <iostream>
#include "c0513.h"

using namespace std;

int main()
{
	Handle h;

	h.initialize();
	cout<<"h.read()  = "<<h.read()<<endl;
	h.change(3);
	cout<<"h.read()  = "<<h.read()<<endl;
	h.cleanup();



}
