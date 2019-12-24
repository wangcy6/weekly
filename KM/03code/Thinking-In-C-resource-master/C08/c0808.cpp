#include <iostream>

using namespace std;

long	a[] = {1, 2, 3, 4, 5};
long	b[] = {6, 7, 8, 9, 10}; 

//这两者的声明性质都一样, 都代表一个指向const long常量的指针；
const long 	*p1 = a;
long const	*p2 = b;

//要使用指针本身成为常量应该把const放在*后面
//这样就能更改指针指向的内容而不能更改指针本身了.
long *const	p3 = a;


int
main()
{
	//指针指向的内容是个常量，能够修改指针本身, 但是不能通过指针修改指向
	//地址的内容
	for(int i = 0; i < sizeof a / sizeof *a; i++) {
		cout<<*p1++<<endl;
		//*p1 = 2;//Error
		cout<<*p2++<<endl;
		//*p2 = 3;
	}
	return 0;
}
