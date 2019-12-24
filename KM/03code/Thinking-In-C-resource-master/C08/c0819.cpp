//类中有const成员函数，const成员函数只能对于const对象调用
//类中的常量要在初始化列表里面进行初始化


class ConstMember {
	float mf;
	const float cmf;
	ConstMember();
}

ConstMember::ConstMember(float ff = 1.0f)
	:
	mf(ff), cmf(ff)
{}

int
main(void)
{
	ConstMember c(1.2);
	return 0;
}
