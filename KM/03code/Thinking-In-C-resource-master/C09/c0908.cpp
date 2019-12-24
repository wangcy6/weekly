/*
 *Dan Saks指出，在一个正真的工程里面，在类里直接定义
 *成员函数，会造成类接口混乱，导致类难以使用，也就是
 *说，类的声明里面应该只有类的接口，而没有类成员函数
 *的定义，若想让成员函数变成内敛函数，则需要在定义的
 *时候加上inline的关键字．这是一种编程风格.大家可以
 *参考一下．
 *用拉丁文来描述就是in situ
 */

#include <iostream>
#include <cstring>

const int sz = 20;

using namespace std;

class Holder {
	private:
		int a[sz];

	public:
		void initialize();

		class Pointer;
		friend Pointer;

		class Pointer {
			private:
				Holder	*h;
				int	*p;

			public:
				void initialize(Holder *rv);
				//Move around in the array:
				void next();
				void previous();
				void top();
				void end();
				//Access values;
				int read();
				void set(int i);
		};
};

inline void Holder::initialize()
{
	memset(a, 0, sz * sizeof(int));
}

inline void Holder::Pointer::initialize(Holder *rv)
{
	h = rv;
	p = rv->a;
}

inline void Holder::Pointer::next()
{
	if (p < &(h->a[sz - 1]))
		p++;
}

inline void Holder::Pointer::previous()
{
	if (p > &(h->a[0]))
		p--;
}

inline void Holder::Pointer::top()
{
	p = &(h->a[0]);
}

inline void Holder::Pointer::end()
{
	p = &(h->a[sz - 1]);
}

inline int Holder::Pointer::read()
{
	return *p;
}

inline void Holder::Pointer::set(int i)
{
	*p = i;
}

int main(void)
{
	Holder	h;
	Holder::Pointer hp, hp2;
	int i;

	h.initialize();
	hp.initialize(&h);
	hp2.initialize(&h);
	for (i = 0; i < sz; i++) {
		hp.set(i);
		hp.next();
	}

	hp.top();
	hp2.end();
	for (i = 0; i < sz; i++) {
		cout << "hp = " << hp.read()
			<< ", hp2 = " << hp2.read() << endl;
		hp.next();
		hp2.previous();
	}
	return 0;
}
