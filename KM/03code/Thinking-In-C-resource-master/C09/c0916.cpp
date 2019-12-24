/*
 *预处理器经常用来处理字符串定义，字符串拼接和标志粘贴
 *字符串定义只需要在前面加上#即可将需要的标志符转换为字符串；
 *字符串拼接，使用##来实现2个字符串的拼接；
 *有关预处理器的更多特征可以参考Arthur Griffith写的<<GCC技术参考大全>>,
 *GCC编译器是开发人员从windows平台转向linux平台不得不了解的工具．
 */

//题意就要要求用户从命令行输入一个字符串，然后我们通过循环来处理
//这个字符串，循环一次丢掉一个字母,然后通过DEBUG宏来打印这个字符串．

#include <cstdio>
#include <iostream>
using namespace std;

#define	 DEBUG(x) cout << #x " = " << x << endl;
int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage : %s string\n", argv[0]);
		return -1;
	}
	else {
		//用户输入后的字符串的首地址储存在argv[1]里
		//将argv[1]里的字符串保存在input里，然后调用
		//string的成员函数erase来完成去掉字母这个操作
		string input = argv[1];
		int l = input.length();
		//注意因为每删除一个字母, input长度会发生变化
		//所以要事先保存输入字符串的长度
		for (int i = 0; i < l; i++) {
			input.erase(input.begin());
			DEBUG(input);
		}

	}


	return 0;
}
