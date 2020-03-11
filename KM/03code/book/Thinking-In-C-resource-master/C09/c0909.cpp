/*
 *使用内联函数修改第八章的StringStack.cpp
 *只需要将简单的成员函数在类的内部定义即可，
 *或者采用in situ
 */
#include <iostream>
#include <cstring>
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

string iceCream[] = {
	"pralines & Cream", 
	"fudge ripple", 
	"jamocha almond fudge", 
	"wild mountian blackbery", 
	"raspberry sorbet", 
	"lemon swirl", 
	"rocky road", 
	"deep chocolate fudge" 
};

const int iCsz = sizeof iceCream / sizeof *iceCream;

int main(void)
{
	StringStack	ss;
	for (int i = 0; i < iCsz; i++)
		ss.push(&iceCream[i]);
	const string *cp;
	while ((cp = ss.pop()) != 0)
		cout<< *cp <<endl;
	return 0;
}
