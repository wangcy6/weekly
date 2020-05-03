//汇编代码用GCC编译器生成的方法是加上-S选项
//生成的汇编文件分别为c0922.s c0922_1.s
//区别是内联函数生成了一个为section和weak标志
//并且在主函数里多了一个text标志
//囧！对汇编不熟悉的结果，并不能看出2者实质上的不同
int f()
{
	int a;
	return a;
}

int main(void)
{
	f();
	return 0;
}
