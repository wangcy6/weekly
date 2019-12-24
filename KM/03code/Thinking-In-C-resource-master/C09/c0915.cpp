/*
 *本题是来测量非内联构造函数与内联构造函数之间在效率上的差别，
 *通过使用前面已经定义好的Time类来实现计时．也可以通过用GNU profile.
 *也就是gprof工具来测量，gprof使用方法在下面的链接
 *http://www.ibm.com/developerworks/cn/linux/l-gnuprof.html
 */

//可能是我的测量方法有误，导致内联与非内联构造函数的时间基本一样
//构造函数花费时间太短，无法测量

#include "c0912.h"
#include <iostream>
using namespace std;

class StringStack {
	static const int size = 100;
	const string* stack[size];
	int index;
	public:
	StringStack() : index(0)
	{
		memset(stack, 0, size * sizeof(string*));
	}
	void push(const string *s)
	{
		if (index < size)
			stack[index++] = s;
	}
	const string* pop()
	{
		if (index > 0) {
			const string* rv = stack[--index];
			stack[index] = 0;
			return rv;
		}
		return 0;
	}
};


class StringStackNoneInline {
	static const int size = 100;
	const string* stack[size];
	int index;
	public:
	StringStackNoneInline();
	void push(const string *s)
	{
		if (index < size)
			stack[index++] = s;
	}
	const string* pop()
	{
		if (index > 0) {
			const string* rv = stack[--index];
			stack[index] = 0;
			return rv;
		}
		return 0;
	}
};

StringStackNoneInline::StringStackNoneInline() : index(0)
{
	memset(stack, 0, size * sizeof(string*));
}

#define RUNTIMES 1000000000
int main(void)
{
	Time	startInline;
	for (int i = 0; i < RUNTIMES; i++)
		StringStack	a;
	Time	endInline;
	std::cout<<startInline.ascii()<<std::endl;
	std::cout<<endInline.ascii()<<std::endl;
	std::cout<<"Inline constructor:"<<endInline.delta(&startInline)<<std::endl;

	Time	startNoneInline;
	for (int i = 0; i < RUNTIMES; i++)
		StringStackNoneInline	b;
	Time	endNoneInline;
	std::cout<<startNoneInline.ascii()<<std::endl;
	std::cout<<endNoneInline.ascii()<<std::endl;
	std::cout<<"NoneInline constructor:"<<endNoneInline.delta(&startNoneInline)<<std::endl;

	return 0;
}
