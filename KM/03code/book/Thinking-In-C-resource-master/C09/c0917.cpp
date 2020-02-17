/*
 *TRACE宏的原型如下：
 *#define TRACE(s) cerr << #s << endl; s
 *不足的地方在于如果当用户调用这个宏而没有在
 *宏前后加上{}, 会只在循环或者条件语句里面
 *执行第一条语句;比如说:
 *if (conditation)
 *        TRACE(s);
 *那么宏展开后的原型为:
 * if (conditation)
 *        cerr << #s <<endl;
 * s;
 *s无论条件是否成立都会执行，这是错误的，所以改进
 *方案是用, 代替;，这样无论用户是否为宏加上花括号，
 *s都会在条件语句里面执行了．
 *
 */
#include <iostream>
using namespace std;

/*
 *需要注意的是，这里的输出是cerr，而不是cout，cerr是
 *标准错误输出，cout是标准输出，cin是标准输入，这是不
 *一样．可参考<<UNIX环境高级编程>>第三章．
 */
#define TRACEOLD(s) cerr << #s << endl; s

#define TRACE(s) cerr << #s << endl, s

int main(void)
{
	//原来TRACE宏，cout语句只被执行了一次
	for (int i = 0; i < 2; i++)
		TRACEOLD(cout<<"It`s wrong!"<<endl;);
	//改进后的TRACE宏，cout语句执行了两次
	for (int i = 0; i < 2; i++)
		TRACE(cout<<"It`s ok!"<<endl;);
	return 0;
}
