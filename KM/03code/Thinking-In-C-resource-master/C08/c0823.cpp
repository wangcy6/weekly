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
	int	noneConstFunc();
	int	constFunc() const;
};

ConstFunc::ConstFunc(int ii)
	:i(ii)
{}

//非const成员函数
int
ConstFunc::noneConstFunc()
{
	return ++i;
}

//const成员函数
int
ConstFunc::constFunc() const
{
	return i;
}

int
main(void)
{
	const ConstFunc cc(11);
	ConstFunc nc(12);

	//非const对象调用非const成员函数
	nc.noneConstFunc();
	//const对象调用const成员函数
	cc.constFunc();

	return 0;
}
