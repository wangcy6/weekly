/*
 *宏通常用来简化我们经常会编写的代码功能，减少我们的工作量;
 *为每一个成员变量编写一个或两个访问器方法是一项十分枯燥的任务.
 *为了避免重复性的工作, 我们通常提供一些宏列宏来帮助我们简化工作;
 *例如在cocos2D游戏引擎里面，就通过使用宏来定义我们需要的访问器和修改器
 */

#include <iostream>
using namespace std;

#define FILEED(index) char string##index

#define	FIND(i)	string##i;

class A {
	public:
	FILEED(1);
	FILEED(2);
	FILEED(3);
	char getByIndex(int i)
	{
		std::string s;
		s += (char)(i + '0');
		return s;
	}
};

int main(void)
{
	A	a;
	a.getByIndex(1) = 'a';
	cout << a.getByIndex(1) << endl;
	return 0;
}
