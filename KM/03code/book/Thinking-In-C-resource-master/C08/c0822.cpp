/*
 *考查const成员函数的定义和声明
 *const成员函数的声明和定义必须同时加上const，
 *编译器和连接程序都要检查const
 *这是为了加深程序员对const的理解，这个函数
 *是const，可以被const对象调用，这个函数不会
 *修改对象的任何值;只要是不会修改数据成员的
 *函数都应该加上const修饰. 
 */

class X {
	int i;
	public:
	X(int ii);
	int f() const;
};


X::X(int ii)
	:i(ii)
{}

/*
 * 如果定义的时候不加上const会出现下面这个编译错误
 *c0822.cpp:24:1: error: prototype for ‘int X::f()’ does not match any in class ‘X’
 *         X::f()
 *         ^
 *         c0822.cpp:15:6: error: candidate is: int X::f() const
 *          int f() const;
 */
int
X::f() const
{
	return i;
}

int
main(void)
{
	return 0;
}
