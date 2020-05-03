#include <iostream>
//c++编程思想作者使用的是<string>头文件，在编译环境下不能通过
//故使用<csting>头文件
#include <cstring>

using namespace std;

/*
 *MyString类和StringStack的声明和定义，笔者为了
 *方面大家查看省去了头文件这个步骤，不建议大家
 *这么做
 */
class MyString {
	string memberString;	
	public:
	MyString(const string ss);
	void print() const;
};

MyString::MyString(const string ss)
	:memberString(ss)
{}

//常量对象只能被常量成员函数调用，故要加上const限定符
void
MyString::print() const
{
	cout<<memberString<<endl;
}

/*StringStack的声明和定义*/
class StringStack {
	static const int size = 100;
	const MyString* stack[size];
	int index;
	public:
	StringStack();
	void push(const MyString*);
	const MyString* pop();
};

StringStack::StringStack():
	index(0)
{
	memset(stack, 0, size * sizeof (MyString*));
}

void
StringStack::push(const MyString* ss)
{
	if (index < size)
		stack[index++] = ss;
}

//此处返回的是常量对象指针
const MyString*
StringStack::pop()
{
	if (index > 0) {
		const MyString* rv = stack[--index];
		stack[index] = 0;
		return rv;
	}
	return NULL;
}

int
main(void)
{
	StringStack	stack;

	//用初始化构造函数构造一个字符串常量数组
	MyString	my[] = {
		MyString("hello"), 
		MyString("programmer"), 
		MyString("It`s a nice day"), 
		MyString("keep do it"), 
		MyString("Never give up") 
	};

	//字符串常量指针入栈，注意存的是指针，所以采用取地址操作
	for (int i = 0; i < sizeof my / sizeof *my; i++) {
		stack.push(&my[i]);
	}

	//返回的是一个常量对象指正，故只有常量成员函数才能调用
	const MyString* cm;
	for (int i = 0; i < sizeof my / sizeof *my; i++) {
		//注意此处cm是指针，直接进行赋值即可不需要进行取地址操作
		cm = stack.pop();
		cm->print();
	}

	return 0;
}

