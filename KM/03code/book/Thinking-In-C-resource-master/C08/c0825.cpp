/*
 *如果想要建立一个const成员函数，但是仍然想在对象里面改变某些数据．
 *这时候有2种方法：
 *第一种：在c0824.cpp中我们看到的编译器错误是提示我们无法将const
 *对象转换为this指针，因为在const成员函数内部它实际是一个const指针, 
 *所以我们只需要进行强制转换即可：
 *接c0824.cpp中的const成员函数
 *int ConstFunc::constMember() const
 *{
 *        return (ConstFunc*(this))->i++;//已经过时
 *        //更标准的做法是
 *        （const_cast<ConstFunc*>(this)->i++;
 *}
 *
 *然而因为这一切是在函数内部进行的, 客户程序员可能看不到这些，所以
 *为了告诉客户程序员我们在const里面进行了一些数据修改，来表示一个
 *特定的数据成员可以在一个const对象里面被修改, 用mutable关键字来进行
 *声明即可达到这一点.
 */

class Z {
	int	i;
	mutable int	j;
	public:
	Z();
	void f() const;
};

Z::Z()
	:i(0), j(0)
{}

void
Z::f() const
{
	//i++;//错误
	j++;//ok
}

int
main(void)
{
	Z z;
	return 0;
}
