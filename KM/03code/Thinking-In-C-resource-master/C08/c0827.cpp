//volatile成员变量，与const成员变量相对应告诉编译器
//不要做任何关于这个变量的假设，需要的时候即重新读这个
//变量;
//volatile对象不能调用非volatile成员函数，因为他不知道
//这个函数是否保持更新volatile成员变量

class X {
	volatile int	i;
	public:
	X();
	void nonVolatile();
	void volatileFunc() volatile;
};

X::X()
	:i(0)
{}

void
X::nonVolatile()
{
	i++;
}

void
X::volatileFunc() volatile
{
	i--;
}

int
main(void)
{
	X x;
	volatile X vx;

	x.nonVolatile();
	//c0827.cpp:37:17: error: passing ‘volatile X’ as ‘this’ argument 
	//of ‘void X::nonVolatile()’ discards qualifiers [-fpermissive]
	//vx.nonVolatile();
	//vx.nonVolatile();

	x.volatileFunc();
	vx.volatileFunc();
	return 0;
}
