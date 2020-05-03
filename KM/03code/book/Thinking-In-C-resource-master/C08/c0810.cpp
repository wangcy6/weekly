#include <iostream>

using namespace std;

int
main(void)
{
	char a[] = "This is a const char* const pointer";

	//指向常量的常量指针是不能通过指针修改地址内容的，
	//也不能修改指针指向的内容．
	const char* const ptr = a;
	cout<<ptr<<endl;

	//c0810.cpp:12:7: error: assignment of read-only location ‘*(const char*)ptr’
	// *ptr = 'a';
	//c0810.cpp:13:5: error: increment of read-only variable ‘ptr’
	//  ptr++;

}
