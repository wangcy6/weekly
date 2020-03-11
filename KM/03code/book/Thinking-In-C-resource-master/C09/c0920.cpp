#include "../require.h"
#include <iostream>
#include <cstdio>
using namespace std;

int main(int argc, char *argv[])
{
	//需要２个命令行参数
	requireArgs(argc, 2);
	//需要第二个命令行参数范围为5~10
	if (5 <= atoi(argv[1]) && atoi(argv[1]) <= 10) {
		ifstream in(argv[2]);
		assure(in, argv[2]);
		cout << "Open file success!\n";
	} else {
		fprintf(stderr, "The first Argument[%s]  must in 5~10\n", argv[1]);
	}
	return 0;
}
