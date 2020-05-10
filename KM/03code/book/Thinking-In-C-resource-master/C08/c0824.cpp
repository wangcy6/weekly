/*
 *本题主要考查const对象和const成员函数之间的调用
 *const对象只能调用const成员函数，这样才能保证
 *成员函数不会修改const对象，编译器也会阻止你这
 *么做．
 *非const对象则任何成员函数都能够调用，因为成员
 *函数无需保证任何事情，只需要它能够被正确调用即可.
 */

class ConstFunc {
	int i;
	public:
	ConstFunc(int ii);
	int	noneConstMember();
	int	constMember() const;
};

ConstFunc::ConstFunc(int ii)
	:i(ii)
{}

//非const成员函数
int
ConstFunc::noneConstMember()
{
	return ++i;
}

//const成员函数
int
ConstFunc::constMember() const
{
	//尝试从const成员函数里面调用非const成员函数
	//c0824.cpp:38:18: error: passing ‘const ConstFunc’ as ‘this’ argument of
	//‘int ConstFunc::noneConstMember()’ discards qualifiers [-fpermissive]
	//noneConstMember();
	//不能将const对象的转换为this参数
	return i;
}

int
main(void)
{
	return 0;
}
