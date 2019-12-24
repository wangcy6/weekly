int
main(void)
{
	return 0;
}

/*
 *这个题主要考查c和c++　const的差别。
 *第一点:
 *c语言中const默认为外部连接。
 *c++中默认为内部连接, 若要使const能够被其他
 *文件访问，则必须在定义的时候使用extern关键字。
 *举例说明：

 //file1.c
 //const int i = 1024;
 //
 //file2.c
 //
 //#include <stdio.h>
 //extern const int i;//代表访问外部连接
 //int
 //main(void)
 //{
 //	printf("%d\n", i);
 //	return 0;
 //}
 
 //使用c编译器不需要在const int i 前面加extern进行修饰
 //也可以访问到i;
 //然而使用c++编译器是访问不到i的；
 */


/*
 *第二点应该是考查编译器是否会为i变量分配内存空间，在c语言中
 *const定义的常量是会分配内存的，意味着能在编译期间访问他的值；
 *还是刚刚那个例子
 */

//file1.c
//const int i = 1024;
//int array[i];//在c语言中编译是会出错的，因为i会占用内存，然而
//c编译器不知道他在编译期间的值。
//
//但是在c++中对const的使用情况不同，可能不会给const变量分配空间
//编译不会出错，c++编译器会将其当做一个常量处理，进行常量折叠.
//当c++对const进行常量折叠的时候，不会为其分配内存空间。
//这个要根据数据的复杂性和编译器性能来决定.
//具体原因查看TheSummaryOfConst.c
//
//我们可以通过查看程序大小来验证c++编译器件是否为const常量分配空间
//file1.c
//const int i = 1;
//int
//main(void)
//{
//	return 0;
//}
////g++编译后无论是否在const前面加extern程序大小都是固定的。
//具体原因等我询问Mr. Rago后在进行测试，可能是我的测试方法
//不对;
 
