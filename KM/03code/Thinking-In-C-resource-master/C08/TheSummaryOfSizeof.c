#include <stdio.h>
#include <stdlib.h>

void test(char a[])
{
	/*
	 *打印的大小为指针的大小;不能期望通过sizeof指针的大小来计算数组的大小。
	 *另外需要注意的是指针和数组名只要在作为函数参数传递的时候,
	 *两者的意思才是相等的，也就是说数组会被当做指针，但是在其他任何情况
	 *下都不要将两者混为一谈，具体原因可参考　《C专家编程》第四章和第九章;
	 */
	printf("%d\n", sizeof(a));
}

int
main(void)
{
	char	a[] = "qwerasdf";
	/*打印大小为数组a的大小9, 因为字符串常量包含一个字符串结束符, 所以大小为8＋1*/ 
	/*使用sizeof而不使用strlen的原因是因为sizeof的实现为一个宏, 而后者为一个函数*/
	printf("%d\n", sizeof(a));

	char	*b = "qwerasdf";
	/*打印的大小为指针的大小，而不是指针指向空间的大小*/ 
	printf("%d\n", sizeof(b));

	char	*c = malloc(100);
	/*打印的大小为指针的大小，而不是指针指向空间的大小*/ 
	printf("%d\n", sizeof(c));
	free(c);
	return (0);
}
