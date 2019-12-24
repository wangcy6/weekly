#include <iostream>
#include "c0501.h"

int main()
{
	CLsy lsy;
	//lsy.i = 0;
	// error: ‘int CLsy::i’ is private
	//lsy.j = 0;
	//error: ‘int CLsy::j’ is protected
	lsy.k = 0;
}
