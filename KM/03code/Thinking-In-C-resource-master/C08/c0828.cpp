//创建一个空类，使用强制转换来调用一个已经存在的类的成员函数
//c语言的void指针允许任何类型的指针进行赋值
//因为指针的占用的空间都是一样的，所以void*允许进行公开的赋值
class bird {
	public:
	void fly();
};

void
bird::fly()
{}

class rock {
};

int
main(void)
{
	rock	r;
	void	*vptr = &r;
	bird	*bptr = (bird*)vptr;
	bptr->fly();
	return 0;
}
