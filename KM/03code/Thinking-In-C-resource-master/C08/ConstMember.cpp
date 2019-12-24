class X {
	int	i;
	public:
	X(int i);
	int f() const;
};

X::X(int i):i(i) {

}

/*const 修饰成员函数定义和声明必须同时存在，否则编译器会把他们成一个不同的函数*/
int
X::f() const {
	return i;
}

int
main(void)
{
	X x1(10);
	const X x2(20);
	x1.f();
	x2.f();
	return 0;
}
