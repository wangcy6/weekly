#include "c0804.h"

int
main(void)
{
	return 0;
}

//file1.h
//
//#ifndef _CONST_H
//#define _CONST_H
//
//const int global = 10;
//
//#endif //_CONST_H
//
//file1.c
//
//#include "file1.h"
//
//int
//main(void)
//{
//	return 0;
//}
//
//file2.c
//
//#include "file1.h"
//
////编译的时候使用cc -x c++　file1.c file2.c
//没有问题
//当时用c编译器的时候
//cc -x c file1.c file2.c
//会出现重复定义的错误提示, 因为c语言中const的默认是
//外部连接的
