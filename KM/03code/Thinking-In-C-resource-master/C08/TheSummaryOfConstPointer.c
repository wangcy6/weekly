#include <iostream>

using namespace std;

int
main(void)
{
	int	c = 10;
	int	c1 = 11;
	const int	*a; /*定义一个指向常量的指针*/ 
	//*a = 12; /*不能通过指针来修改该值*/ 
	a = &c;
	cout<<*a<<endl;
	//但是可以更改指针指向的内容
	a = &c1;
	cout<<*a<<endl;

	int *const	b = &c; /*定义一个指针常量，指针的地址是确定的，但是地址的内容可以通过指针进行修改*/ 
	//定义的时候必须初始化
	cout<<*b<<endl;
	*b = 12;
	cout<<*b<<endl;
	//可以通过指针修改指向的内容，但是不能修改指针指向的地址
	//b = &c1;//编译错误

	const int* const cc = &c; /*定义一个指向常量的常量指针，指针的地址和内容都不能修改*/ 
	cout<<*b<<endl;




	return 0;
}
