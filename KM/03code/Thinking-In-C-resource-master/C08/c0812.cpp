#include <iostream>

using namespace std;

//定义一个字符串数组
char cp[] = "good day!";

//定义一个字符串常量数组任何一个试图修改该数组的操作, 
//编译器都会报错．
//所以这个时候在不在char前面加const都无关紧要了．
//我个人建议还是要加上好些
char *tp = "common programmer";
//更好的做法
const char *tpBetterWay = "good programmer!";
int
main(void) 
{
	cout<<cp<<endl;
	cp[0] = 'a';
	cout<<cp[0]<<endl;
	cout<<cp<<endl;

	return 0;
}


