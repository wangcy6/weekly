//ConstTemporary.cpp

class X {
};

X
f()
{
	return X();
}

void
g1(X&)
{} //pass by reference 

void
g2(const X&)
{} //pass by const reference 

int
main(void)
{
	//建立一个临时对象，临时对象为const，所以g1是错误的
	//g1(f());
	//g2接受一个const引用，故是正确的
	g2(f());
	return 0;
}
