#include <iostream>

//删除空格后
#define	F(x)	(x + 1)

int main(void)
{
	std::cout<<F(1)<<std::endl;
	return 0;
}

/*
 *编译错误
 *c0901.cpp: In function ‘int main()’:
 *c0901.cpp:3:12: error: ‘x’ was not declared in this scope
 * #define F (x) (x + 1)
 *            ^
 *c0901.cpp:7:13: note: in expansion of macro ‘F’
 *  std::cout<<F(1)<<std::endl;
 *             ^
 */
