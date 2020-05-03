#include <iostream>
using namespace std;

const char a[] = "this is a test!!";
//注意[]和指针的区别，这两者在c语言中只有在作为函数参数
//传递的时候才被认为是相同的，其他任何时候都应该尽量避免
//将两者混合使用;

int main()
{
	cout<<a<<endl;
	//c0806.cpp:11:7: error: assignment of read-only location ‘a[0]’
	// a[0] = 'a';
	// 字符串常量也不能被修改

}
